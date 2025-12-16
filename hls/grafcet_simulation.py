#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
A0 System Grafcet Controller Simulation (Pseudo-code)
=====================================================

此檔案模擬 A0 系統的 Grafcet 控制邏輯。
它包含了 A1~A8 各模組的模擬介面，以及核心的離散事件控制器。

架構：
1. Data Structures: 定義輸入、輸出、內部變數。
2. Modules (A1-A7): 模擬各功能模組的行為（空函式，僅模擬狀態變化）。
3. Controller (A8): 實現 Grafcet 邏輯（步驟、變遷、動作）。

"""

import time
import random
from enum import Enum
from dataclasses import dataclass, field
from typing import Dict, Any, Optional

# --- 1. 定義狀態與訊號 ---

class ModuleStatus(Enum):
    IDLE = "IDLE"
    RUNNING = "RUNNING"
    DONE = "DONE"
    ERROR = "ERROR"

@dataclass
class SystemInputs:
    """模擬外部輸入"""
    user_start: bool = False
    file_uploaded: bool = False
    user_reset: bool = False
    download_done: bool = False

@dataclass
class SystemOutputs:
    """模擬系統輸出"""
    ui_state: str = "IDLE"
    progress: int = 0
    current_message: str = ""
    report_ready: bool = False

@dataclass
class InternalState:
    """內部變數與旗標"""
    session_id: Optional[str] = None
    parsed_info: Optional[dict] = None
    similar_patents: Optional[dict] = None
    patent_outline: Optional[dict] = None
    draft_content: Optional[dict] = None
    diagram_index: Optional[dict] = None
    final_doc: Optional[str] = None
    
    # 錯誤計數器
    retry_count: int = 0
    max_retries: int = 3

# --- 2. 模組模擬 (A1 ~ A7) ---
# 這些是 "空函式"，但具備完整的 I/O 簽名與狀態模擬邏輯

class A1_UI_Management:
    def __init__(self):
        self.status = ModuleStatus.IDLE

    def run(self, enable: bool, inputs: SystemInputs) -> ModuleStatus:
        """
        A1: 處理使用者互動
        Input: enable (由 Controller 觸發), system inputs
        Output: ModuleStatus
        """
        if not enable:
            self.status = ModuleStatus.IDLE
            return self.status

        # 模擬 UI 行為
        print("[A1] UI Active: 等待/處理使用者操作...")
        
        # 這裡僅回傳狀態，實際觸發由 Inputs 決定
        self.status = ModuleStatus.RUNNING
        return self.status

    def lock_ui(self):
        print("[A1] UI Locked")

    def unlock_ui(self):
        print("[A1] UI Unlocked")
    
    def show_download(self):
        print("[A1] Show Download Link")

class A2_Document_Parsing:
    def simulate_processing(self, raw_file: bool) -> (ModuleStatus, Optional[dict]):
        """
        A2: 文件解析
        """
        if not raw_file:
            return ModuleStatus.IDLE, None
            
        print("[A2] Parsing Document...")
        # 模擬處理時間與成功率
        time.sleep(0.5) 
        success = True # random.choice([True, True, False]) # 模擬偶發錯誤
        
        if success:
            print("[A2] Parsing Success")
            return ModuleStatus.DONE, {"title": "Demo Patent", "content": "..."}
        else:
            print("[A2] Parsing Failed")
            return ModuleStatus.ERROR, None

class A3_Patent_Search:
    def simulate_processing(self, parsed_info: dict) -> (ModuleStatus, Optional[dict]):
        """
        A3: 專利檢索
        """
        if not parsed_info:
            return ModuleStatus.IDLE, None

        print("[A3] Searching Patents...")
        time.sleep(0.5)
        print("[A3] Search Done")
        return ModuleStatus.DONE, {"patents": ["US123", "CN456"]}

class A4_Outline_Generation:
    def simulate_processing(self, parsed_info: dict, search_results: dict) -> (ModuleStatus, Optional[dict]):
        """
        A4: 大綱生成
        """
        if not parsed_info or not search_results:
            return ModuleStatus.IDLE, None
            
        print("[A4] Generating Outline...")
        time.sleep(0.5)
        print("[A4] Outline Created")
        return ModuleStatus.DONE, {"chapters": ["1. Title", "2. Field", "..."]}

class A5_Content_Writing:
    def simulate_processing(self, outline: dict) -> (ModuleStatus, Optional[dict]):
        """
        A5: 內容撰寫
        """
        if not outline:
            return ModuleStatus.IDLE, None

        print("[A5] Writing Content...")
        time.sleep(0.8)
        print("[A5] Drafting Complete")
        return ModuleStatus.DONE, {"abstract": "...", "claims": "...", "description": "..."}

class A6_Diagram_Generation:
    def simulate_processing(self, draft_content: dict) -> (ModuleStatus, Optional[dict]):
        """
        A6: 圖表生成
        """
        if not draft_content:
            return ModuleStatus.IDLE, None

        print("[A6] Generating Diagrams...")
        time.sleep(0.5)
        print("[A6] Diagrams Ready")
        return ModuleStatus.DONE, {"diagrams": ["fig1.png", "fig2.mmd"]}

class A7_Document_Merging:
    def simulate_processing(self, draft: dict, diagrams: dict) -> (ModuleStatus, Optional[str]):
        """
        A7: 文件整合
        """
        if not draft or not diagrams:
            return ModuleStatus.IDLE, None
            
        print("[A7] Merging Document...")
        time.sleep(0.4)
        print("[A7] Final DOCX Ready")
        return ModuleStatus.DONE, "/path/to/final.docx"


# --- 3. Grafcet Controller (A8) ---

class GrafcetController:
    """
    A8 流程控制核心
    模擬 Grafcet 的 Steps, Transitions 和 Actions
    """
    def __init__(self):
        # 初始化模組
        self.a1 = A1_UI_Management()
        self.a2 = A2_Document_Parsing()
        self.a3 = A3_Patent_Search()
        self.a4 = A4_Outline_Generation()
        self.a5 = A5_Content_Writing()
        self.a6 = A6_Diagram_Generation()
        self.a7 = A7_Document_Merging()
        
        # 系統狀態
        self.inputs = SystemInputs()
        self.outputs = SystemOutputs()
        self.internal = InternalState()
        
        # Grafcet Steps (Active Flags)
        # S0: Init, S1: Setup, S2: Parse, S3: Search, S4: Outline
        # S5: Write, S6: Param, S7: Merge, S8: Finish, S99: Error
        self.steps = {f"S{i}": False for i in range(9)}
        self.steps["S99"] = False # Error Step
        
        # Initial Step
        self.steps["S0"] = True
        
        # Store failed step for retry logic
        self.last_failed_step = None

    def update_inputs(self, new_inputs: SystemInputs):
        self.inputs = new_inputs

    def step_cycle(self):
        """
        執行一次 Grafcet 掃描週期
        1. 評估變遷 (Evaluate Transitions)
        2. 更新步驟 (Update Steps)
        3. 執行動作 (Execute Actions)
        """
        
        # --- 1. Evaluate Transitions ---
        # 為了模擬真實 PLC/Grafcet，這裡使用此狀態的快照來決定下一狀態
        next_steps = self.steps.copy()
        
        # Tr0: S0 -> S1 (Start Condition)
        if self.steps["S0"] and self.inputs.user_start and self.inputs.file_uploaded:
            print(">>> Transition Tr0: Start Process")
            next_steps["S0"] = False
            next_steps["S1"] = True

        # Tr1: S1 -> S2 (Session Created)
        elif self.steps["S1"] and self.internal.session_id:
            print(">>> Transition Tr1: Session Ready")
            next_steps["S1"] = False
            next_steps["S2"] = True

        # Tr2: S2 -> S3 (Parsing Done)
        elif self.steps["S2"] and self.internal.parsed_info:
            print(">>> Transition Tr2: Parsing Done")
            next_steps["S2"] = False
            next_steps["S3"] = True
        
        # Tr_Err_S2: S2 -> S99 (Parsing Failed) - Simplified simulation trigger provided in Action phase logic
        
        # Tr3: S3 -> S4 (Search Done)
        elif self.steps["S3"] and self.internal.similar_patents:
            print(">>> Transition Tr3: Search Done")
            next_steps["S3"] = False
            next_steps["S4"] = True

        # Tr4: S4 -> S5 (Outline Done)
        elif self.steps["S4"] and self.internal.patent_outline:
            print(">>> Transition Tr4: Outline Done")
            next_steps["S4"] = False
            next_steps["S5"] = True

        # Tr5: S5 -> S6 (Writing Done)
        elif self.steps["S5"] and self.internal.draft_content:
            print(">>> Transition Tr5: Content Written")
            next_steps["S5"] = False
            next_steps["S6"] = True

        # Tr6: S6 -> S7 (Diagrams Done)
        elif self.steps["S6"] and self.internal.diagram_index:
            print(">>> Transition Tr6: Diagrams Ready")
            next_steps["S6"] = False
            next_steps["S7"] = True

        # Tr7: S7 -> S8 (Merge Done)
        elif self.steps["S7"] and self.internal.final_doc:
            print(">>> Transition Tr7: Merging Done -> Finish")
            next_steps["S7"] = False
            next_steps["S8"] = True

        # Tr8: S8 -> S0 (Reset)
        elif self.steps["S8"] and (self.inputs.user_reset or self.inputs.download_done):
            print(">>> Transition Tr8: Reset to Idle")
            next_steps["S8"] = False
            next_steps["S0"] = True
            # Reset internals
            self.internal = InternalState()
            self.inputs.user_start = False # Reset trigger

        # TrRetry: S99 -> Last Step
        elif self.steps["S99"] and self.internal.retry_count < self.internal.max_retries:
            print(f">>> Transition TrRetry: Retry {self.last_failed_step} (Attemp {self.internal.retry_count + 1})")
            next_steps["S99"] = False
            next_steps[self.last_failed_step] = True
            self.internal.retry_count += 1
            
        # TrFail: S99 -> S8 (Fatal Error)
        elif self.steps["S99"] and self.internal.retry_count >= self.internal.max_retries:
            print(">>> Transition TrFail: Max Retries Reached -> Finish with Error")
            next_steps["S99"] = False
            next_steps["S8"] = True
            self.outputs.current_message = "Critical Error: Process Failed"

        # Apply Step Updates
        self.steps = next_steps


        # --- 2. Execute Actions (Based on Active Steps) ---
        
        # S0: Idle
        if self.steps["S0"]:
            self.a1.run(True, self.inputs) # Enable UI
            self.outputs.ui_state = "IDLE"
            self.outputs.progress = 0

        # S1: Initialization
        if self.steps["S1"]:
            self.a1.lock_ui()
            # Simulate create session
            if not self.internal.session_id:
                time.sleep(0.2)
                self.internal.session_id = "UUID-1234-5678"
                print(f"[A8] Session Created: {self.internal.session_id}")

        # S2: Parsing (A2)
        if self.steps["S2"]:
            status, result = self.a2.simulate_processing(raw_file=True)
            if status == ModuleStatus.DONE:
                self.internal.parsed_info = result
            elif status == ModuleStatus.ERROR:
                self._trigger_error("S2")

        # S3: Searching (A3)
        if self.steps["S3"]:
            status, result = self.a3.simulate_processing(self.internal.parsed_info)
            if status == ModuleStatus.DONE:
                self.internal.similar_patents = result
            elif status == ModuleStatus.ERROR:
                self._trigger_error("S3")

        # S4: Outline (A4)
        if self.steps["S4"]:
            status, result = self.a4.simulate_processing(self.internal.parsed_info, self.internal.similar_patents)
            if status == ModuleStatus.DONE:
                self.internal.patent_outline = result
            elif status == ModuleStatus.ERROR:
                self._trigger_error("S4")

        # S5: Writing (A5)
        if self.steps["S5"]:
            status, result = self.a5.simulate_processing(self.internal.patent_outline)
            if status == ModuleStatus.DONE:
                self.internal.draft_content = result
            elif status == ModuleStatus.ERROR:
                self._trigger_error("S5")

        # S6: diagram (A6)
        if self.steps["S6"]:
            status, result = self.a6.simulate_processing(self.internal.draft_content)
            if status == ModuleStatus.DONE:
                self.internal.diagram_index = result
            elif status == ModuleStatus.ERROR:
                self._trigger_error("S6")

        # S7: Merge (A7)
        if self.steps["S7"]:
            status, result = self.a7.simulate_processing(self.internal.draft_content, self.internal.diagram_index)
            if status == ModuleStatus.DONE:
                self.internal.final_doc = result
            elif status == ModuleStatus.ERROR:
                self._trigger_error("S7")

        # S8: Finish
        if self.steps["S8"]:
            self.a1.unlock_ui()
            self.a1.show_download()
            self.outputs.report_ready = True
            self.outputs.progress = 100
            self.outputs.ui_state = "DONE"
            print("[A8] Process Finished. Report Generated.")

        # S99: Error Handling
        if self.steps["S99"]:
            print(f"[A8] Handling Error from {self.last_failed_step}")
            # Logic handled in transitions
            pass

    def _trigger_error(self, source_step):
        """Helper to force jump to error step (simulating internal error detection)"""
        print(f"!!! Error detected in {source_step}")
        self.steps[source_step] = False
        self.steps["S99"] = True
        self.last_failed_step = source_step


# --- 4. Main Simulation Loop ---

def main():
    print("=== Starting A0 Grafcet System Simulation ===")
    
    controller = GrafcetController()
    
    # 模擬場景：使用者上傳檔案並開始
    print("\n[Scenario] User uploads file and clicks Start")
    controller.update_inputs(SystemInputs(user_start=True, file_uploaded=True))
    
    # Run loop
    for cycle in range(20): # Simulate 20 PLC cycles
        print(f"\n--- Cycle {cycle+1} ---")
        controller.step_cycle()
        
        # 檢查是否到達完成狀態，若是，模擬使用者下載並重置
        if controller.steps["S8"]:
            print("\n[Scenario] User downloads file")
            controller.update_inputs(SystemInputs(user_start=False, file_uploaded=False, download_done=True))

        # Check if back to S0
        if controller.steps["S0"] and cycle > 5:
            print("System returned to IDLE.")
            break
            
        time.sleep(0.5)

if __name__ == "__main__":
    main()
