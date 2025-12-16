/**
 * A0 Integrated System Software Synthesis (Reverse Engineering Output)
 * ==================================================================
 *
 * 本檔案為最終合成的系統軟體 (Pseudo-code Simulation)，整合了：
 * 1. Grafcet 系統控制器 (System Controller) - 負責流程控制 (A8)
 * 2. Datapath 驅動程式 (HW Drivers) - 負責驅動硬體加速器
 * 3. 硬體加速器模擬 (HW Accelerators) - A2 模式匹配與 A3 向量運算
 *
 * 架構圖概念：
 * [ Application Layer (A1, A4-A7) ] <--> [ A8 System Controller ] <--> [ Mod A2/A3 ] <--> [ Drivers ] <--> [ HW IPs ]
 *
 * 編譯指令: gcc -o system_integrated hls/system_integration.c -lm
 * 執行指令: ./system_integrated
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

// ============================================================================
// PART 1: 硬體加速器層 (Hardware Abstraction Layer & Simulation)
// ============================================================================

// --- Hardware Register Map ---
#define BASE_ADDR_SIM_ENGINE  0x40000000
#define BASE_ADDR_PAT_MATCHER 0x40010000

#define REG_CTRL_OFFSET    0x00
#define REG_STATUS_OFFSET  0x04
// A3 Specific
#define REG_VEC_A_ADDR     0x10
#define REG_VEC_B_ADDR     0x18
#define REG_VEC_LEN        0x20
#define REG_RESULT_SCORE   0x24
// A2 Specific
#define REG_TXT_ADDR       0x10
#define REG_TXT_SIZE       0x14
#define REG_PAT_ID         0x18
#define REG_MATCH_COUNT    0x20

// --- Mock Hardware IP ---
typedef struct {
    uint32_t ctrl;
    uint32_t status;
    uint32_t reg_file[16];
    bool is_busy;
} MockIP;

MockIP ip_sim_engine = {0};
MockIP ip_pat_matcher = {0};

// HW Access Simulation
void hw_write_reg(uint32_t base_addr, uint32_t offset, uint32_t value) {
    MockIP *ip = (base_addr == BASE_ADDR_SIM_ENGINE) ? &ip_sim_engine : &ip_pat_matcher;
    
    if (offset == REG_CTRL_OFFSET) {
        ip->ctrl = value;
        if (value & 0x01) { // Start bit
            ip->status &= ~0x02; // Clear Idle
            ip->status &= ~0x01; // Clear Done
            ip->is_busy = true;
            // printf("[HW-Log] IP 0x%X Start.\n", base_addr);
        }
    } else if (offset >= 0x10) {
        int idx = (offset - 0x10) / 4;
        if (idx < 16) ip->reg_file[idx] = value;
    }
}

uint32_t hw_read_reg(uint32_t base_addr, uint32_t offset) {
    MockIP *ip = (base_addr == BASE_ADDR_SIM_ENGINE) ? &ip_sim_engine : &ip_pat_matcher;

    // Simulate completion on read status
    if (ip->is_busy) {
        ip->is_busy = false; 
        ip->status |= 0x01; // Done
        ip->status |= 0x02; // Idle
        
        if (base_addr == BASE_ADDR_SIM_ENGINE) {
            float score = 0.5f + ((float)rand() / (float)RAND_MAX) * 0.5f; // Random 0.5-1.0
            ip->reg_file[(REG_RESULT_SCORE - 0x10)/4] = (uint32_t)(score * 65536);
        }
        if (base_addr == BASE_ADDR_PAT_MATCHER) {
            ip->reg_file[(REG_MATCH_COUNT - 0x10)/4] = rand() % 20 + 1; // Random 1-20 matches
        }
    }

    if (offset == REG_STATUS_OFFSET) return ip->status;
    if (offset >= 0x10) {
        int idx = (offset - 0x10) / 4;
        if (idx < 16) return ip->reg_file[idx];
    }
    return 0;
}

// --- Driver API ---

typedef struct { uint32_t base_addr; } Handle;

void Driver_A3_Init(Handle *h) {
    h->base_addr = BASE_ADDR_SIM_ENGINE;
    hw_write_reg(h->base_addr, REG_CTRL_OFFSET, 0x02); // Reset
}

float Driver_A3_ComputeSimilarity(Handle *h, void *vecA, void *vecB, int len) {
    hw_write_reg(h->base_addr, REG_VEC_LEN, len);
    hw_write_reg(h->base_addr, REG_VEC_A_ADDR, (uint32_t)(uintptr_t)vecA);
    hw_write_reg(h->base_addr, REG_VEC_B_ADDR, (uint32_t)(uintptr_t)vecB);
    hw_write_reg(h->base_addr, REG_CTRL_OFFSET, 0x01); // Start
    
    while(!(hw_read_reg(h->base_addr, REG_STATUS_OFFSET) & 0x01)); // Poll
    
    return (float)hw_read_reg(h->base_addr, REG_RESULT_SCORE) / 65536.0f;
}

void Driver_A2_Init(Handle *h) {
    h->base_addr = BASE_ADDR_PAT_MATCHER;
}

int Driver_A2_MatchPattern(Handle *h, const char *txt, int size, int pat_id) {
    hw_write_reg(h->base_addr, REG_TXT_ADDR, (uint32_t)(uintptr_t)txt);
    hw_write_reg(h->base_addr, REG_TXT_SIZE, size);
    hw_write_reg(h->base_addr, REG_PAT_ID, pat_id);
    hw_write_reg(h->base_addr, REG_CTRL_OFFSET, 0x01); // Start
    
    while(!(hw_read_reg(h->base_addr, REG_STATUS_OFFSET) & 0x01)); // Poll
    
    return (int)hw_read_reg(h->base_addr, REG_MATCH_COUNT);
}


// ============================================================================
// PART 2: 系統控制器層 (System Controller - Grafcet Implementation)
// ============================================================================

// --- Data Structures ---

typedef enum { STATUS_IDLE, STATUS_DONE, STATUS_ERROR } ModuleStatus;
typedef enum { S0, S1, S2, S3, S4, S5, S6, S7, S8, S99 } StepID;

typedef struct {
    bool user_start;
    bool file_uploaded;
    bool download_done;
} SystemInputs;

typedef struct {
    char session_id[40];
    bool parsed_ready;
    bool search_ready;
    bool outline_ready;
    bool content_ready;
    bool diagrams_ready;
    bool final_doc_ready;
    int retry_count;
} InternalState;

bool steps[20];
SystemInputs sys_in = {0};
InternalState sys_state = {0};
Handle hA2, hA3; // Hardware Handles

// --- Module Simulations (Integrating Drivers) ---

// A1: UI
void Mod_A1_UI() {
    // printf("[A1] UI Running...\n");
}

// A2: Document Parsing (Accelerated)
ModuleStatus Mod_A2_Parsing(bool enable) {
    if (!enable) return STATUS_IDLE;
    
    printf("\n[A2] Starting Accelerated Document Parsing...\n");
    
    // Simulate reading a doc
    const char *mock_doc = "Patent Document Content...";
    int len = strlen(mock_doc);

    // Call HW Accelerator to find key sections
    int field_matches = Driver_A2_MatchPattern(&hA2, mock_doc, len, 1); // Pattern 1: Tech Field
    int bg_matches = Driver_A2_MatchPattern(&hA2, mock_doc, len, 2);    // Pattern 2: Background
    
    printf("     -> [HW] Pattern Matcher found %d Field tags, %d Background tags.\n", field_matches, bg_matches);
    
    if (field_matches > 0) return STATUS_DONE;
    return STATUS_ERROR;
}

// A3: Patent Search (Accelerated)
ModuleStatus Mod_A3_Search(bool enable) {
    if (!enable) return STATUS_IDLE;
    
    printf("\n[A3] Starting Accelerated Patent Search...\n");
    
    float vec_target[128];
    float vec_candidate[128];
    
    // Call HW Accelerator for similarity check
    float max_score = 0.0f;
    for(int i=0; i<3; i++) {
        float score = Driver_A3_ComputeSimilarity(&hA3, vec_target, vec_candidate, 128);
        printf("     -> [HW] SimEngine Candidate %d Score: %.4f\n", i, score);
        if(score > max_score) max_score = score;
    }
    
    if (max_score > 0.6) return STATUS_DONE; // Threshold
    return STATUS_ERROR;
}

// A4: Outline (SW)
ModuleStatus Mod_A4_Outline(bool enable) {
    if(!enable) return STATUS_IDLE;
    printf("\n[A4] Structure Planning (SW)...\n");
    return STATUS_DONE;
}

// A5: Content (SW)
ModuleStatus Mod_A5_Content(bool enable) {
    if(!enable) return STATUS_IDLE;
    printf("\n[A5] Content Generation (SW Agent)...\n");
    return STATUS_DONE;
}

// A6: Diagrams (SW)
ModuleStatus Mod_A6_Diagrams(bool enable) {
    if(!enable) return STATUS_IDLE;
    printf("\n[A6] Diagram Generation (Metmaid)...\n");
    return STATUS_DONE;
}

// A7: Merging (SW)
ModuleStatus Mod_A7_Merging(bool enable) {
    if(!enable) return STATUS_IDLE;
    printf("\n[A7] Document Merging & Formatting...\n");
    return STATUS_DONE;
}

// --- Controller Logic (A8) ---

void Controller_Init() {
    memset(steps, 0, sizeof(steps));
    steps[S0] = true;
    sys_state.retry_count = 0;
    
    // Init HW Drivers
    Driver_A2_Init(&hA2);
    Driver_A3_Init(&hA3);
}

void Controller_Cycle() {
    bool next_steps[20];
    memcpy(next_steps, steps, sizeof(steps));
    
    // --- EVALUATE TRANSITIONS ---
    
    // Tr0: Start
    if (steps[S0] && sys_in.user_start && sys_in.file_uploaded) {
        printf(">>> [Trans] User Start -> S1 (Init)\n");
        next_steps[S0] = false; next_steps[S1] = true;
    }
    // Tr1: Init Done -> S2
    else if (steps[S1] && strlen(sys_state.session_id) > 0) {
        printf(">>> [Trans] Session Ready -> S2 (Parsing)\n");
        next_steps[S1] = false; next_steps[S2] = true;
    }
    // Tr2: A2 Done -> S3
    else if (steps[S2] && sys_state.parsed_ready) {
        printf(">>> [Trans] Parsing Done -> S3 (Search)\n");
        next_steps[S2] = false; next_steps[S3] = true;
    }
    // Tr3: A3 Done -> S4
    else if (steps[S3] && sys_state.search_ready) {
        printf(">>> [Trans] Search Done -> S4 (Outline)\n");
        next_steps[S3] = false; next_steps[S4] = true;
    }
    // Tr4: A4 Done -> S5
    else if (steps[S4] && sys_state.outline_ready) {
        printf(">>> [Trans] Outline Done -> S5 (Writing)\n");
        next_steps[S4] = false; next_steps[S5] = true;
    }
    // Tr5: A5 Done -> S6
    else if (steps[S5] && sys_state.content_ready) {
        printf(">>> [Trans] Writing Done -> S6 (Diagrams)\n");
        next_steps[S5] = false; next_steps[S6] = true;
    }
    // Tr6: A6 Done -> S7
    else if (steps[S6] && sys_state.diagrams_ready) {
        printf(">>> [Trans] Diagrams Done -> S7 (Merging)\n");
        next_steps[S6] = false; next_steps[S7] = true;
    }
    // Tr7: A7 Done -> S8
    else if (steps[S7] && sys_state.final_doc_ready) {
        printf(">>> [Trans] Finish -> S8 (Idle/Download)\n");
        next_steps[S7] = false; next_steps[S8] = true;
    }
    // Tr8: Download Done -> S0
    else if (steps[S8] && sys_in.download_done) {
        printf(">>> [Trans] Reset -> S0\n");
        next_steps[S8] = false; next_steps[S0] = true;
        // Reset State
        memset(&sys_state, 0, sizeof(sys_state));
        sys_in.user_start = false;
        sys_in.download_done = false;
    }

    // Apply Transition
    memcpy(steps, next_steps, sizeof(steps));
    
    // --- EXECUTE ACTIONS ---
    
    if (steps[S1]) {
        if (strlen(sys_state.session_id) == 0) {
            strcpy(sys_state.session_id, "UUID-SIM-001");
            printf("    [Action] Session Created: %s\n", sys_state.session_id);
        }
    }
    if (steps[S2] && !sys_state.parsed_ready) {
        if (Mod_A2_Parsing(true) == STATUS_DONE) sys_state.parsed_ready = true;
    }
    if (steps[S3] && !sys_state.search_ready) {
        if (Mod_A3_Search(true) == STATUS_DONE) sys_state.search_ready = true;
    }
    if (steps[S4] && !sys_state.outline_ready) {
        if (Mod_A4_Outline(true) == STATUS_DONE) sys_state.outline_ready = true;
    }
    if (steps[S5] && !sys_state.content_ready) {
        if (Mod_A5_Content(true) == STATUS_DONE) sys_state.content_ready = true;
    }
    if (steps[S6] && !sys_state.diagrams_ready) {
        if (Mod_A6_Diagrams(true) == STATUS_DONE) sys_state.diagrams_ready = true;
    }
    if (steps[S7] && !sys_state.final_doc_ready) {
        if (Mod_A7_Merging(true) == STATUS_DONE) sys_state.final_doc_ready = true;
    }
    if (steps[S8]) {
        printf("    [Action] Waiting for User Download...\n");
        sys_in.download_done = true; // Auto simulate user action
    }
}

// ============================================================================
// MAIN SIMULATION ENTRY
// ============================================================================

int main() {
    srand(time(NULL));
    
    printf("============================================================\n");
    printf("   A0 Integrated System Software Synthesis (Simulated)    \n");
    printf("============================================================\n");
    printf("SW/HW Partitioning:\n");
    printf(" - SW: Controller, Outline, Content, Diagram, Merging\n");
    printf(" - HW: Document Parsing (Matcher), Patent Search (SimEngine)\n");
    printf("============================================================\n\n");
    
    Controller_Init();
    
    // Simulate User Trigger
    printf("[User] Uploading File...\n");
    sys_in.file_uploaded = true;
    printf("[User] Clicking Start...\n");
    sys_in.user_start = true;
    
    // Run System Cycles
    int cycle = 0;
    while(cycle < 15) {
        // printf("\n--- System Cycle %d ---\n", cycle);
        Controller_Cycle();
        
        if (steps[S0] && cycle > 5) {
            printf("\n>>> System Reset Complete. Idle.\n");
            break;
        }
        
        usleep(200000); // 0.2s tick
        cycle++;
    }
    
    return 0;
}
