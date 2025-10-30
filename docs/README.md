# 專案功能設計文件

此目錄存放專利寫作自動化系統的功能架構設計文件。

> 💡 **快速開始**: 先閱讀 [ARCHITECTURE.md](ARCHITECTURE.md) 了解系統架構總覽

---

## 📁 目錄結構

```
docs/
├── README.md                           # 本文件
├── ARCHITECTURE.md                     # 系統架構總覽 (開發者入口)
├── A0_system_idef0.md                  # 系統頂層 IDEF0 架構
├── A1_UI_Management_IDEF0.md           # 使用者介面管理模組
├── A2_Document_Parsing_IDEF0.md        # 文件解析模組
├── A3_Patent_Search_IDEF0.md           # 專利檢索模組
├── A4_Outline_Generation_IDEF0.md      # 大綱生成模組
├── A5_Content_Writing_IDEF0.md         # 內容撰寫模組
├── A6_Diagram_Generation_IDEF0.md      # 圖表生成模組
├── A7_Document_Merging_IDEF0.md        # 文件合併模組
├── A8_Workflow_Control_IDEF0.md        # 工作流程控制模組
└── troubleshooting/                    # 開發除錯記錄（獨立子目錄）
    ├── README.md
    └── Mermaid_*.md
```

---

## 🎯 IDEF0 架構設計

### 什麼是 IDEF0？

**IDEF0**（Integration Definition for Function Modeling）是一種結構化的系統分析和設計方法，使用圖形化方式描述系統功能、輸入、輸出、控制和機制。

### 本專案的 IDEF0 架構層級

```
A-0: 系統邊界圖（Context Diagram）
 │
 └─ A0: 頂層功能分解（8 個主要模組）
     │
     ├─ A1: 使用者介面管理（4 個子功能）
     ├─ A2: 文件解析（4 個子功能）
     ├─ A3: 專利檢索（4 個子功能）
     ├─ A4: 大綱生成（4 個子功能）
     ├─ A5: 內容撰寫（4 個子功能）
     ├─ A6: 圖表生成（4 個子功能）
     ├─ A7: 文件合併（4 個子功能）
     └─ A8: 工作流程控制（4 個子功能）
```

### ICOM 分析架構

每個功能模組都使用 **ICOM 分析**描述：

| 元素 | 英文 | 說明 | 圖示位置 |
|------|------|------|---------|
| **I** | Input | 輸入資料或資訊 | 功能方塊左側 ← |
| **C** | Control | 控制條件或規則 | 功能方塊上方 ↓ |
| **O** | Output | 輸出結果或產品 | 功能方塊右側 → |
| **M** | Mechanism | 執行機制或資源 | 功能方塊下方 ↑ |

---

## 📊 系統架構文件導覽

### 從哪裡開始閱讀？

#### 0. 系統架構總覽 (建議從這裡開始)
👉 [ARCHITECTURE.md](ARCHITECTURE.md)

**內容概要**:
- 系統 Workflow 設計圖
- 完整專案目錄結構
- 執行流程和資料流轉
- 技術棧總覽
- 品質標準

**適合對象**:
- 所有開發者 (新手入門必讀)
- 專案管理者
- 需要快速了解系統的人員

---

#### 1. 系統整體架構
👉 [A0_system_idef0.md](A0_system_idef0.md)

**內容概要**：
- A-0 系統邊界圖（Context Diagram）
- A0 頂層功能分解（8 個模組的關係）
- 完整的 ICOM 分析表
- 系統資料流圖
- 技術實作建議

**適合對象**：
- 專案管理者
- 系統架構師
- 需要了解全局的開發者

---

#### 2. 各模組詳細設計

##### A1: 使用者介面管理
👉 [A1_UI_Management_IDEF0.md](A1_UI_Management_IDEF0.md)

**子功能**：
- A1.1: 檔案上傳處理
- A1.2: 使用者參數設定
- A1.3: 進度顯示與回饋
- A1.4: 結果預覽與下載

**技術棧**：Streamlit, Python

---

##### A2: 文件解析
👉 [A2_Document_Parsing_IDEF0.md](A2_Document_Parsing_IDEF0.md)

**子功能**：
- A2.1: DOCX 檔案讀取
- A2.2: 技術資訊提取
- A2.3: 結構化資料轉換
- A2.4: 提取結果驗證

**技術棧**：markitdown, python-docx, JSON

---

##### A3: 專利檢索
👉 [A3_Patent_Search_IDEF0.md](A3_Patent_Search_IDEF0.md)

**子功能**：
- A3.1: 關鍵字提取
- A3.2: 專利資料庫檢索
- A3.3: 相似度分析
- A3.4: 現有技術報告生成

**技術棧**：Google Patents API, Exa Search API

---

##### A4: 大綱生成
👉 [A4_Outline_Generation_IDEF0.md](A4_Outline_Generation_IDEF0.md)

**子功能**：
- A4.1: 專利章節規劃
- A4.2: 技術特徵映射
- A4.3: 附圖規劃
- A4.4: 大綱驗證與調整

**技術棧**：Claude API, 中國專利法規範

---

##### A5: 內容撰寫
👉 [A5_Content_Writing_IDEF0.md](A5_Content_Writing_IDEF0.md)

**子功能**：
- A5.1: 權利要求書撰寫
- A5.2: 具體實施方式撰寫
- A5.3: 摘要撰寫
- A5.4: 內容品質檢查

**技術棧**：Claude API, 專利撰寫規範

**品質要求**：
- 具體實施方式 > 10,000 字
- 術語一致性 100%
- 符合《專利審查指南》

---

##### A6: 圖表生成
👉 [A6_Diagram_Generation_IDEF0.md](A6_Diagram_Generation_IDEF0.md)

**子功能**：
- A6.1: 流程圖生成
- A6.2: 結構圖生成
- A6.3: 時序圖生成
- A6.4: 圖表編號與說明

**技術棧**：Mermaid.js, 自動圖表生成

---

##### A7: 文件合併
👉 [A7_Document_Merging_IDEF0.md](A7_Document_Merging_IDEF0.md)

**子功能**：
- A7.1: 章節順序組織
- A7.2: 圖表插入與引用
- A7.3: 格式統一處理
- A7.4: 最終文件生成

**技術棧**：Markdown, Pandoc（可選）

---

##### A8: 工作流程控制
👉 [A8_Workflow_Control_IDEF0.md](A8_Workflow_Control_IDEF0.md)

**子功能**：
- A8.1: Agent 執行排程
- A8.2: 資料流轉管理
- A8.3: 錯誤處理與重試
- A8.4: 執行日誌記錄

**技術棧**：Claude Code Agent SDK, Python

---

## 🔄 系統工作流程

### 標準執行流程

```
1. 使用者上傳 DOCX → A1 (UI Management)
                        ↓
2. 解析技術內容 ←------- A2 (Document Parsing)
         ↓
3. 檢索相似專利 ←------- A3 (Patent Search)
         ↓
4. 生成專利大綱 ←------- A4 (Outline Generation)
         ↓
5. 並行撰寫內容 ←------- A5 (Content Writing)
   │                      - 權利要求書
   │                      - 具體實施方式
   │                      - 摘要
   ↓
6. 生成技術圖表 ←------- A6 (Diagram Generation)
         ↓
7. 合併完整文件 ←------- A7 (Document Merging)
         ↓
8. 輸出 Markdown ←------- A1 (下載結果)

全程監控與協調 ←------- A8 (Workflow Control)
```

### 資料流轉目錄結構

每個專案執行時會建立以下工作目錄：

```
output/temp_[uuid]/
├── 01_input/                    # A2 輸入與輸出
│   ├── raw_document.docx
│   └── parsed_info.json
├── 02_research/                 # A3 輸出
│   ├── similar_patents.json
│   └── prior_art_analysis.md
├── 03_outline/                  # A4 輸出
│   ├── patent_outline.md
│   └── structure_mapping.json
├── 04_content/                  # A5 輸出
│   ├── abstract.md
│   ├── claims.md
│   └── description.md
├── 05_diagrams/                 # A6 輸出
│   ├── flowcharts/
│   ├── structural_diagrams/
│   └── sequence_diagrams/
├── 06_final/                    # A7 輸出
│   └── complete_patent.md
└── metadata/                    # A8 管理
    ├── project_info.json
    └── agent_logs/
```

---

## 📖 文件閱讀建議

### 針對不同角色的閱讀路徑

#### 專案管理者
1. [A0_system_idef0.md](A0_system_idef0.md) - 系統全貌
2. [A8_Workflow_Control_IDEF0.md](A8_Workflow_Control_IDEF0.md) - 流程控制
3. [A1_UI_Management_IDEF0.md](A1_UI_Management_IDEF0.md) - 使用者介面

#### 前端開發者
1. [A1_UI_Management_IDEF0.md](A1_UI_Management_IDEF0.md) - UI 設計
2. [A0_system_idef0.md](A0_system_idef0.md) - 了解後端 API
3. [A7_Document_Merging_IDEF0.md](A7_Document_Merging_IDEF0.md) - 結果展示

#### 後端開發者
1. [A0_system_idef0.md](A0_system_idef0.md) - 系統架構
2. [A2_Document_Parsing_IDEF0.md](A2_Document_Parsing_IDEF0.md) - 文件處理
3. [A8_Workflow_Control_IDEF0.md](A8_Workflow_Control_IDEF0.md) - Agent 協調
4. [A3_Patent_Search_IDEF0.md](A3_Patent_Search_IDEF0.md) - API 整合

#### AI/Prompt 工程師
1. [A0_system_idef0.md](A0_system_idef0.md) - 系統概覽
2. [A4_Outline_Generation_IDEF0.md](A4_Outline_Generation_IDEF0.md) - 大綱生成
3. [A5_Content_Writing_IDEF0.md](A5_Content_Writing_IDEF0.md) - 內容撰寫
4. [A6_Diagram_Generation_IDEF0.md](A6_Diagram_Generation_IDEF0.md) - 圖表生成

#### 品質保證工程師
1. [A0_system_idef0.md](A0_system_idef0.md) - 測試範圍
2. 所有 A1-A8 模組 - 各模組驗證標準
3. [A8_Workflow_Control_IDEF0.md](A8_Workflow_Control_IDEF0.md) - 錯誤處理

---

## 🛠️ 技術棧總覽

### 核心技術

| 層級 | 技術 | 用途 |
|-----|------|------|
| **AI 引擎** | Claude 3.5 Sonnet | 專利內容生成、分析 |
| **Agent 框架** | Claude Code Agent SDK | 多 Agent 協調 |
| **前端** | Streamlit | 使用者介面 |
| **文件處理** | markitdown, python-docx | DOCX 解析 |
| **專利檢索** | Google Patents API | 專利搜尋 |
| **網頁檢索** | Exa Search API | 技術文件搜尋 |
| **圖表生成** | Mermaid.js | 技術圖表 |
| **資料格式** | JSON, Markdown | 資料交換 |

### 開發工具

- **IDE**: VS Code + Claude Code 擴充套件
- **版本控制**: Git
- **文件格式**: Markdown + Mermaid
- **專案管理**: IDEF0 建模

---

## 📝 文件維護規範

### 新增功能模組

當需要新增功能模組時：

1. **建立新的 IDEF0 文件**
   ```bash
   cp A0_system_idef0.md A9_New_Module_IDEF0.md
   ```

2. **遵循統一結構**
   - 模組概述
   - IDEF0 圖（A-0, A0, A9.1-A9.4）
   - ICOM 分析表
   - 程式碼範例
   - Mermaid 圖表

3. **更新 A0 頂層文件**
   - 在系統架構圖中加入新模組
   - 更新 ICOM 分析表
   - 調整資料流圖

4. **更新本 README**
   - 在目錄結構中加入新文件
   - 在導覽章節中加入說明

### 文件版本控制

所有設計文件的修改都應該：
- 使用 Git 追蹤變更
- Commit 訊息說明修改原因
- 重大修改應標註版本號

### 文件品質標準

✅ 每個模組文件必須包含：
- 清晰的 IDEF0 圖表
- 完整的 ICOM 分析
- 實作範例程式碼
- Mermaid 視覺化圖表

✅ Mermaid 圖表要求：
- 使用 `flowchart` 語法（非 `graph`）
- 避免過度複雜的 `subgraph` 巢狀
- 所有節點使用繁體中文標籤
- 提供圖表說明文字

---

## 🔗 相關資源

### 專案文件
- [專案說明](../專案說明.md) - 專案整體介紹
- [主 README](../README.md) - 快速開始指南
- [除錯記錄](troubleshooting/README.md) - 開發問題排查

### 技術規範
- [中國專利法](https://www.cnipa.gov.cn/) - 專利撰寫規範
- [IDEF0 標準](https://en.wikipedia.org/wiki/IDEF0) - 建模方法論
- [Mermaid 文件](https://mermaid.js.org/) - 圖表語法

### 開發工具
- [Claude Code](https://claude.com/claude-code) - AI 開發環境
- [Streamlit 文件](https://docs.streamlit.io/) - UI 框架
- [Google Patents](https://patents.google.com/) - 專利資料庫

---

## 📞 聯絡資訊

如有關於功能設計的問題或建議：
1. 提交 GitHub Issue
2. 標註標籤：`documentation` 或 `architecture`
3. 引用相關的 IDEF0 文件編號

---

**最後更新**：2025-10-30
**文件版本**：v1.0
**維護者**：專案架構團隊
