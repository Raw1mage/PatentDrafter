/**
 * A0 System Grafcet Controller Simulation (C Implementation)
 * ==========================================================
 *
 * 模擬 A0 系統的 Grafcet 控制邏輯。
 * 包含 A1~A8 各模組的模擬介面，以及核心的離散事件控制器。
 *
 * 架構：
 * 1. Data Structures: 定義輸入、輸出、內部變數。
 * 2. Modules (A1-A7): 模擬各功能模組的行為（空函式，僅模擬狀態變化）。
 * 3. Controller (A8): 實現 Grafcet 邏輯（步驟、變遷、動作）。
 *
 * 編譯指令: gcc -o grafcet_sim grafcet_simulation.c
 * 執行指令: ./grafcet_sim
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> // for sleep

// --- 1. 定義狀態與訊號 ---

typedef enum {
    STATUS_IDLE,
    STATUS_RUNNING,
    STATUS_DONE,
    STATUS_ERROR
} ModuleStatus;

typedef struct {
    bool user_start;
    bool file_uploaded;
    bool user_reset;
    bool download_done;
} SystemInputs;

typedef struct {
    char ui_state[20];
    int progress;
    char current_message[100];
    bool report_ready;
} SystemOutputs;

typedef struct {
    char session_id[40];
    bool parsed_ready;
    bool search_ready;
    bool outline_ready;
    bool content_ready;
    bool diagrams_ready;
    bool final_doc_ready;

    // 錯誤計數器
    int retry_count;
    int max_retries;
} InternalState;

// Steps definition
typedef enum {
    S0, S1, S2, S3, S4, S5, S6, S7, S8, S99
} StepID;

// Boolean array for steps activity
bool steps[20]; 
StepID last_failed_step;

// --- 2. 模組模擬 (A1 ~ A7) ---

// A1: 介面管理
void A1_run(bool enable, SystemInputs *inputs) {
    if (!enable) return;
    printf("[A1] UI Active: Waiting/Processing User Ops...\n");
}

void A1_lock_ui() {
    printf("[A1] UI Locked\n");
}

void A1_unlock_ui() {
    printf("[A1] UI Unlocked\n");
}

void A1_show_download() {
    printf("[A1] Show Download Link\n");
}

// A2: 文件解析
ModuleStatus A2_simulate(bool raw_file_presents) {
    if (!raw_file_presents) return STATUS_IDLE;
    printf("[A2] Parsing Document...\n");
    // sleep(1); // Simulate processing time
    printf("[A2] Parsing Success\n");
    return STATUS_DONE;
}

// A3: 專利檢索
ModuleStatus A3_simulate(bool parsed_ready) {
    if (!parsed_ready) return STATUS_IDLE;
    printf("[A3] Searching Patents...\n");
    // sleep(1);
    printf("[A3] Search Done\n");
    return STATUS_DONE;
}

// A4: 大綱生成
ModuleStatus A4_simulate(bool parsed_ready, bool search_ready) {
    if (!parsed_ready || !search_ready) return STATUS_IDLE;
    printf("[A4] Generating Outline...\n");
    // sleep(1);
    printf("[A4] Outline Created\n");
    return STATUS_DONE;
}

// A5: 內容撰寫
ModuleStatus A5_simulate(bool outline_ready) {
    if (!outline_ready) return STATUS_IDLE;
    printf("[A5] Writing Content...\n");
    // sleep(1);
    printf("[A5] Drafting Complete\n");
    return STATUS_DONE;
}

// A6: 圖表生成
ModuleStatus A6_simulate(bool content_ready) {
    if (!content_ready) return STATUS_IDLE;
    printf("[A6] Generating Diagrams...\n");
    // sleep(1);
    printf("[A6] Diagrams Ready\n");
    return STATUS_DONE;
}

// A7: 文件整合
ModuleStatus A7_simulate(bool content_ready, bool diagrams_ready) {
    if (!content_ready || !diagrams_ready) return STATUS_IDLE;
    printf("[A7] Merging Document...\n");
    // sleep(1);
    printf("[A7] Final DOCX Ready\n");
    return STATUS_DONE;
}


// --- 3. Grafcet Controller (A8) ---

SystemInputs g_inputs = {0};
SystemOutputs g_outputs = {0};
InternalState g_internal = {0};

void A8_init() {
    // Initialize Steps
    for(int i=0; i<20; i++) steps[i] = false;
    steps[S0] = true; // Initial Step
    
    // Init Internal State
    g_internal.max_retries = 3;
    g_internal.retry_count = 0;
    
    strcpy(g_outputs.ui_state, "IDLE");
}

void A8_trigger_error(StepID source) {
    printf("!!! Error detected in S%d\n", source);
    steps[source] = false;
    steps[S99] = true;
    last_failed_step = source;
}

// 模擬一個 scan cycle
void A8_step_cycle() {
    // Temp next state storage
    bool next_steps[20];
    memcpy(next_steps, steps, sizeof(steps));
    bool transition_occurred = false;

    // --- 1. Evaluate Transitions ---
    
    // Tr0: S0 -> S1
    if (steps[S0] && g_inputs.user_start && g_inputs.file_uploaded) {
        printf(">>> Transition Tr0: Start Process\n");
        next_steps[S0] = false;
        next_steps[S1] = true;
        transition_occurred = true;
    }
    // Tr1: S1 -> S2 (Session Created)
    else if (steps[S1] && strlen(g_internal.session_id) > 0) {
        printf(">>> Transition Tr1: Session Ready\n");
        next_steps[S1] = false;
        next_steps[S2] = true;
        transition_occurred = true;
    }
    // Tr2: S2 -> S3 (Parsing Done)
    else if (steps[S2] && g_internal.parsed_ready) {
        printf(">>> Transition Tr2: Parsing Done\n");
        next_steps[S2] = false;
        next_steps[S3] = true;
        transition_occurred = true;
    }
    // Tr3: S3 -> S4 (Search Done)
    else if (steps[S3] && g_internal.search_ready) {
        printf(">>> Transition Tr3: Search Done\n");
        next_steps[S3] = false;
        next_steps[S4] = true;
        transition_occurred = true;
    }
    // Tr4: S4 -> S5 (Outline Done)
    else if (steps[S4] && g_internal.outline_ready) {
        printf(">>> Transition Tr4: Outline Done\n");
        next_steps[S4] = false;
        next_steps[S5] = true;
        transition_occurred = true;
    }
    // Tr5: S5 -> S6 (Content Done)
    else if (steps[S5] && g_internal.content_ready) {
        printf(">>> Transition Tr5: Content Written\n");
        next_steps[S5] = false;
        next_steps[S6] = true;
        transition_occurred = true;
    }
    // Tr6: S6 -> S7 (Diagrams Done)
    else if (steps[S6] && g_internal.diagrams_ready) {
        printf(">>> Transition Tr6: Diagrams Ready\n");
        next_steps[S6] = false;
        next_steps[S7] = true;
        transition_occurred = true;
    }
    // Tr7: S7 -> S8 (Merge Done)
    else if (steps[S7] && g_internal.final_doc_ready) {
        printf(">>> Transition Tr7: Merging Done -> Finish\n");
        next_steps[S7] = false;
        next_steps[S8] = true;
        transition_occurred = true;
    }
    // Tr8: S8 -> S0 (Reset)
    else if (steps[S8] && (g_inputs.user_reset || g_inputs.download_done)) {
        printf(">>> Transition Tr8: Reset to Idle\n");
        next_steps[S8] = false;
        next_steps[S0] = true;
        
        // Reset process variables
        g_internal.parsed_ready = false;
        g_internal.search_ready = false;
        g_internal.outline_ready = false;
        g_internal.content_ready = false;
        g_internal.diagrams_ready = false;
        g_internal.final_doc_ready = false;
        memset(g_internal.session_id, 0, sizeof(g_internal.session_id));
        
        g_inputs.user_start = false; // Reset trigger
        transition_occurred = true;
    }
    // TrRetry: S99 -> Last Step
    else if (steps[S99] && g_internal.retry_count < g_internal.max_retries) {
        printf(">>> Transition TrRetry: Retry S%d (Attempt %d)\n", last_failed_step, g_internal.retry_count + 1);
        next_steps[S99] = false;
        next_steps[last_failed_step] = true;
        g_internal.retry_count++;
        transition_occurred = true;
    } 
    // TrFail: S99 -> S8
    else if (steps[S99] && g_internal.retry_count >= g_internal.max_retries) {
        printf(">>> Transition TrFail: Max Retries Reached -> Finish with Error\n");
        next_steps[S99] = false;
        next_steps[S8] = true;
        strcpy(g_outputs.current_message, "Critical Error: Process Failed");
        transition_occurred = true;
    }

    // Apply updates
    memcpy(steps, next_steps, sizeof(steps));

    // --- 2. Execute Actions ---
    
    if (steps[S0]) {
        A1_run(true, &g_inputs);
        g_outputs.progress = 0;
        strcpy(g_outputs.ui_state, "IDLE");
    }

    if (steps[S1]) {
        A1_lock_ui();
        if (strlen(g_internal.session_id) == 0) {
            usleep(200000); // 0.2s
            strcpy(g_internal.session_id, "UUID-1234-5678");
            printf("[A8] Session Created: %s\n", g_internal.session_id);
        }
    }

    if (steps[S2]) {
        ModuleStatus st = A2_simulate(true);
        if (st == STATUS_DONE) g_internal.parsed_ready = true;
        else if (st == STATUS_ERROR) A8_trigger_error(S2);
    }
    
    if (steps[S3]) {
        ModuleStatus st = A3_simulate(g_internal.parsed_ready);
        if (st == STATUS_DONE) g_internal.search_ready = true;
        else if (st == STATUS_ERROR) A8_trigger_error(S3);
    }

    if (steps[S4]) {
        ModuleStatus st = A4_simulate(g_internal.parsed_ready, g_internal.search_ready);
        if (st == STATUS_DONE) g_internal.outline_ready = true;
        else if (st == STATUS_ERROR) A8_trigger_error(S4);
    }

    if (steps[S5]) {
        ModuleStatus st = A5_simulate(g_internal.outline_ready);
        if (st == STATUS_DONE) g_internal.content_ready = true;
        else if (st == STATUS_ERROR) A8_trigger_error(S5);
    }

    if (steps[S6]) {
        ModuleStatus st = A6_simulate(g_internal.content_ready);
        if (st == STATUS_DONE) g_internal.diagrams_ready = true;
        else if (st == STATUS_ERROR) A8_trigger_error(S6);
    }

    if (steps[S7]) {
        ModuleStatus st = A7_simulate(g_internal.content_ready, g_internal.diagrams_ready);
        if (st == STATUS_DONE) g_internal.final_doc_ready = true;
        else if (st == STATUS_ERROR) A8_trigger_error(S7);
    }

    if (steps[S8]) {
        A1_unlock_ui();
        A1_show_download();
        g_outputs.report_ready = true;
        g_outputs.progress = 100;
        strcpy(g_outputs.ui_state, "DONE");
        printf("[A8] Process Finished. Report Generated.\n");
    }
}


// --- 4. Main Simulation Loop ---

int main() {
    printf("=== Starting A0 Grafcet System Simulation (C) ===\n\n");
    
    A8_init();
    
    // Scenario: User uploads file and clicks Start
    printf("[Scenario] User uploads file and clicks Start\n");
    g_inputs.user_start = true;
    g_inputs.file_uploaded = true;

    // Simulate 20 scans
    for (int cycle = 1; cycle <= 20; cycle++) {
        printf("\n--- Cycle %d ---\n", cycle);
        A8_step_cycle();
        
        // Check finish condition
        if (steps[S8]) {
            printf("\n[Scenario] User downloads file\n");
            g_inputs.download_done = true;
            g_inputs.user_start = false;
        }
        
        // If back to idle
        if (steps[S0] && cycle > 5) {
            printf("System returned to IDLE.\n");
            break;
        }
        
        usleep(500000); // 0.5s
    }

    return 0;
}
