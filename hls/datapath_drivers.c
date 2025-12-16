/**
 * A0 System Hardware Acceleration Datapath Drivers (C Simulation)
 * ===============================================================
 *
 * 本檔案模擬針對 A0 系統中計算密集型任務的硬體加速器驅動程式。
 * 
 * 1. 識別出的加速候選模組：
 *    - [A3 專利檢索]: 向量相似度計算 (Vector Similarity Calculation)。
 *      - 原因: 高維向量點積運算密集，適合 FPGA DSP Slice 管線化加速。
 *    - [A2 文件解析]: 關鍵字模式匹配 (Pattern Matching)。
 *      - 原因: 大量文本的正則表達式匹配，適合 FPGA 有限狀態機 (FSM) 加速。
 *
 * 2. 模擬架構：
 *    - 定義記憶體映射暫存器 (Memory-Mapped Registers)。
 *    - 模擬 AXI-Lite 控制介面與 AXI-Stream 資料流介面。
 *    - 提供 Driver API 供上層軟體呼叫。
 *
 * 編譯指令: gcc -o datapath_sim hls/datapath_drivers.c -lm
 * 執行指令: ./datapath_sim
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

// --- 硬體暫存器定義 (Memory Map) ---

// Base Addresses
#define BASE_ADDR_SIM_ENGINE  0x40000000
#define BASE_ADDR_PAT_MATCHER 0x40010000

// Common Control Registers
#define REG_CTRL_OFFSET    0x00  // Bit 0: Start, Bit 1: Reset, Bit 2: Auto-Restart
#define REG_STATUS_OFFSET  0x04  // Bit 0: Done, Bit 1: Idle, Bit 2: Ready
#define REG_INT_EN_OFFSET  0x08
#define REG_INT_STS_OFFSET 0x0C

// Similarity Engine Specific Registers (A3)
#define REG_VEC_A_ADDR     0x10  // Vector A DDR Address
#define REG_VEC_B_ADDR     0x18  // Vector B DDR Address (can be array base)
#define REG_VEC_LEN        0x20  // Vector Length
#define REG_RESULT_SCORE   0x24  // Output Score (Fixed Point)

// Pattern Matcher Specific Registers (A2)
#define REG_TXT_ADDR       0x10  // Text Buffer Address
#define REG_TXT_SIZE       0x14  // Text Size in bytes
#define REG_PAT_ID         0x18  // Pattern ID to match
#define REG_MATCH_COUNT    0x20  // Result: Number of matches found

// --- 模擬硬體行為 (Hardware Simulation Stub) ---
// 這裡模擬硬體 IP 的行為：讀取暫存器 -> 執行運算 -> 寫回狀態

typedef struct {
    uint32_t ctrl;
    uint32_t status;
    uint32_t reg_file[16]; // 簡化的暫存器堆
    bool is_busy;
} MockIP;

MockIP ip_sim_engine = {0};
MockIP ip_pat_matcher = {0};

// 模擬暫存器寫入 (AXI-Lite Write)
void hw_write_reg(uint32_t base_addr, uint32_t offset, uint32_t value) {
    MockIP *ip = (base_addr == BASE_ADDR_SIM_ENGINE) ? &ip_sim_engine : &ip_pat_matcher;
    
    if (offset == REG_CTRL_OFFSET) {
        ip->ctrl = value;
        // 模擬硬體啟動信號 (PosEdge Start)
        if (value & 0x01) {
            ip->status &= ~0x02; // Clear Idle
            ip->status &= ~0x01; // Clear Done
            ip->is_busy = true;
            printf("[HW-Sim] IP at 0x%X Started. (Pipeline Flush)\n", base_addr);
        }
    } else if (offset >= 0x10) {
        int idx = (offset - 0x10) / 4;
        if (idx < 16) ip->reg_file[idx] = value;
    }
}

// 模擬暫存器讀取 (AXI-Lite Read)
uint32_t hw_read_reg(uint32_t base_addr, uint32_t offset) {
    MockIP *ip = (base_addr == BASE_ADDR_SIM_ENGINE) ? &ip_sim_engine : &ip_pat_matcher;

    // 模擬硬體運算週期完成
    if (ip->is_busy) {
        // 簡單模擬：立即完成
        ip->is_busy = false; 
        ip->status |= 0x01; // Set Done
        ip->status |= 0x02; // Set Idle
        
        // 如果是 Similarity Engine，模擬生成一個隨機分數
        if (base_addr == BASE_ADDR_SIM_ENGINE) {
            // 模擬定點數結果 (Q16.16)
            float score = (float)rand() / (float)RAND_MAX; // 0.0 - 1.0
            uint32_t fixed_score = (uint32_t)(score * 65536);
            ip->reg_file[(REG_RESULT_SCORE - 0x10)/4] = fixed_score;
        }
        
        // 如果是 Pattern Matcher，模擬生成匹配數量
        if (base_addr == BASE_ADDR_PAT_MATCHER) {
            uint32_t matches = rand() % 50; 
            ip->reg_file[(REG_MATCH_COUNT - 0x10)/4] = matches;
        }
    }

    if (offset == REG_STATUS_OFFSET) return ip->status;
    if (offset >= 0x10) {
        int idx = (offset - 0x10) / 4;
        if (idx < 16) return ip->reg_file[idx];
    }
    return 0;
}


// --- 驅動程式 (Driver Software) ---

// 1. Vector Similarity Engine Driver (A3)
// ---------------------------------------------------------

typedef struct {
    uint32_t base_addr;
    uint32_t vec_len;
} SimEngine_Handle;

int SimEngine_Init(SimEngine_Handle *h, uint32_t base) {
    h->base_addr = base;
    h->vec_len = 0;
    // Reset IP
    hw_write_reg(h->base_addr, REG_CTRL_OFFSET, 0x02); // Bit 1 Reset
    hw_write_reg(h->base_addr, REG_CTRL_OFFSET, 0x00);
    return 0;
}

void SimEngine_Config(SimEngine_Handle *h, uint32_t len) {
    h->vec_len = len;
    hw_write_reg(h->base_addr, REG_VEC_LEN, len);
}

float SimEngine_Compute(SimEngine_Handle *h, float *vecA, float *vecB) {
    // 實際上在真實驅動中，這裡會將 Host 指標轉換為 Bus Address (Physical Addr)
    // 這裡僅傳遞模擬地址 (cast pointer to int)
    hw_write_reg(h->base_addr, REG_VEC_A_ADDR, (uint32_t)(uintptr_t)vecA);
    hw_write_reg(h->base_addr, REG_VEC_B_ADDR, (uint32_t)(uintptr_t)vecB);
    
    // Start Engine
    hw_write_reg(h->base_addr, REG_CTRL_OFFSET, 0x01); // Bit 0 Start
    
    // Polling for completion (Data Path Pipeline Latency)
    // 在 HLS 中，ap_done 信號會觸發 REG_STATUS 的 Bit 0
    uint32_t status;
    do {
        status = hw_read_reg(h->base_addr, REG_STATUS_OFFSET);
        // usleep(10); // Wait cycle
    } while (!(status & 0x01)); // Wait for Done bit
    
    // Read Result
    uint32_t raw_res = hw_read_reg(h->base_addr, REG_RESULT_SCORE);
    
    // Clear Interrupt/Done
    hw_write_reg(h->base_addr, REG_INT_STS_OFFSET, 0x01);
    
    // Convert Fixed Point Q16.16 to Float
    return (float)raw_res / 65536.0f;
}


// 2. Pattern Matcher Driver (A2)
// ---------------------------------------------------------

typedef struct {
    uint32_t base_addr;
} PatMatcher_Handle;

int PatMatcher_Init(PatMatcher_Handle *h, uint32_t base) {
    h->base_addr = base;
    return 0;
}

int PatMatcher_Search(PatMatcher_Handle *h, const char *text_buffer, uint32_t size, int pattern_id) {
    // Config DMA Pointers
    hw_write_reg(h->base_addr, REG_TXT_ADDR, (uint32_t)(uintptr_t)text_buffer);
    hw_write_reg(h->base_addr, REG_TXT_SIZE, size);
    hw_write_reg(h->base_addr, REG_PAT_ID, pattern_id);
    
    // Pipeline Start
    hw_write_reg(h->base_addr, REG_CTRL_OFFSET, 0x01);
    
    // Polling
    uint32_t status;
    do {
        status = hw_read_reg(h->base_addr, REG_STATUS_OFFSET);
    } while (!(status & 0x01));
    
    // Get Count
    int count = (int)hw_read_reg(h->base_addr, REG_MATCH_COUNT);
    return count;
}


// --- Main Application (Integration Test) ---

int main() {
    printf("=== A0 System Datapath Driver Simulation ===\n\n");
    
    // 初始化驅動 handles
    SimEngine_Handle hSim;
    SimEngine_Init(&hSim, BASE_ADDR_SIM_ENGINE);
    
    PatMatcher_Handle hPat;
    PatMatcher_Init(&hPat, BASE_ADDR_PAT_MATCHER);
    
    // --- Scenario 1: A2 Document Parsing Acceleration ---
    printf("[A2] Pattern Matcher Accelerator Test:\n");
    const char *doc_content = "The present invention relates to AI... background art... structure...";
    
    // 模擬識別 "technical field" (ID=1)
    int matches = PatMatcher_Search(&hPat, doc_content, 1024, 1);
    printf("  -> Pattern 'Technical Field' (ID:1) found %d times.\n", matches);
    
    // 模擬識別 "claims" (ID=5)
    matches = PatMatcher_Search(&hPat, doc_content, 1024, 5);
    printf("  -> Pattern 'Claims' (ID:5) found %d times.\n", matches);
    

    // --- Scenario 2: A3 Patent Search Acceleration ---
    printf("\n[A3] Similarity Engine Accelerator Test:\n");
    
    float target_vec[768]; // e.g., BERT embedding dimension
    float candidate_vec[768];
    
    SimEngine_Config(&hSim, 768);
    
    // 模擬批次計算相似度 (Datapath Pipelining)
    for (int i = 0; i < 5; i++) {
        // 在真實場景中這些數據存在 DRAM 中
        float score = SimEngine_Compute(&hSim, target_vec, candidate_vec);
        printf("  -> Candidate Patent %d Similarity Score: %.4f (Q16.16 HW Result)\n", i+1, score);
    }

    printf("\nDatapath Simulation Complete.\n");
    return 0;
}
