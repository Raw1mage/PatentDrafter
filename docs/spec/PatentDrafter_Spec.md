# PatentDrafter 產品規格書

> **📋 規格說明**
>
> 本文檔描述 **PatentDrafter**（專利起草助手）的產品規格，作為開發目標和功能定義。
>
> ⚠️ 文檔中描述的功能代表**應該實現的目標**，而非當前已實現的功能。
>
> 開發團隊應以本規格為基準進行系統設計和實作。

---

## 📌 產品概述

**PatentDrafter** 是一個基於 Streamlit 的 Web 應用程式，專門用於自動生成專利申請文件。

### 核心功能
- 用戶上傳 DOCX 格式的技術交底書
- 系統調用 Claude AI 自動生成完整專利申請文件
- 實時顯示生成過程的詳細日誌
- 提供進程控制和歷史管理功能

### 目標用戶
- 企業專利部門人員
- 專利事務所專利工程師
- 研發人員

---

## 🎯 核心運作原理

### 多 Agent 協作架構

這是一個**純 Prompt Engineering 專案**，採用多 Agent 流水線架構：

```
使用者輸入 (技術交底書.docx)
    ↓
[主 Agent 專案經理] (定義於 CLAUDE.md)
    ↓
建立工作目錄結構 (output/temp_[uuid]/)
    ↓
按順序呼叫 8 個專業子 Agent
    ↓
輸出完整專利文件 (complete_patent.md)
```

### 子 Agent 流水線（8 個階段）

| 階段 | 子 Agent | 核心任務 | 輸入 | 輸出 |
|------|---------|----------|------|------|
| 1 | input-parser | 解析技術交底書 | raw_document.docx | parsed_info.json |
| 2 | patent-searcher | 檢索相似專利 | parsed_info.json | similar_patents.json |
| 3 | outline-generator | 生成專利大綱 | parsed + similar | patent_outline.md |
| 4 | abstract-drafter | 起草摘要 | outline | abstract.md |
| 5 | claims-drafter | 起草權利要求 | outline + abstract | claims.md |
| 6 | description-drafter | 起草說明書主體 | outline + claims | description.md (>10000字) |
| 7 | diagram-generator | 生成 Mermaid 圖表 | description + structure | *.mmd 檔案 |
| 8 | markdown-merger | 合併最終文件 | 所有 md + 圖表 | complete_patent.md |

### 資料流轉機制

- **結構化傳遞** - 使用 JSON 檔案在 Agent 間傳遞結構化資料
- **版本控制** - 每個階段輸出保留多版本（v01, v02...）
- **依賴管理** - 嚴格按順序執行，後一個 Agent 依賴前一個的輸出
- **品質把關** - 每個階段完成後驗證輸出格式和內容完整性

---

## 🛠️ 技術實作原理

### 核心架構說明

⚠️ **重要**: 這是一個**純 Prompt Engineering 專案**，沒有傳統程式碼基礎。

#### 實作方式

```
Claude Code (AI IDE)
    ↓
讀取 CLAUDE.md 指令檔
    ↓
主 Agent (Claude AI) 根據指令協調工作
    ↓
呼叫子 Agent (也是 Claude AI，不同的 prompt)
    ↓
透過檔案系統傳遞資料
    ↓
輸出最終專利文件
```

#### 關鍵特點

- ✅ **無程式碼** - 沒有 Python/JavaScript 等傳統程式語言
- ✅ **純 Prompt** - 所有邏輯都在 `.md` 檔案中定義
- ✅ **LLM 驅動** - 完全依賴 Claude AI 的推理能力
- ✅ **檔案通訊** - Agent 之間透過讀寫檔案交換資訊

### Agent 協作機制

#### 主 Agent (定義於 CLAUDE.md)

- **角色**: 專案經理
- **職責**: 協調、品質把控、工作流程管理
- **實作**: 透過詳細的自然語言指令定義行為

#### 子 Agent (定義於 .claude/agents/*.md)

- `input-parser.md` - 文件解析專家
- `patent-searcher.md` - 專利檢索專家
- `outline-generator.md` - 大綱生成專家
- `abstract-drafter.md` - 摘要起草專家
- `claims-drafter.md` - 權利要求起草專家
- `description-drafter.md` - 說明書起草專家
- `diagram-generator.md` - 圖表生成專家
- `markdown-merger.md` - 文件整合專家

#### 通訊方式

```
Agent A 寫入 → JSON/Markdown 檔案 → Agent B 讀取
```

### 外部工具整合 (MCP 伺服器)

雖然核心邏輯是純 Prompt，但有整合外部工具：

#### MCP (Model Context Protocol) 工具

- `google-patents-mcp` - 專利檢索 API
- `exa-mcp-server` - 網頁搜尋 API
- `markitdown` - 文件格式轉換 (DOCX → Markdown)

#### 配置方式 (.mcp.json)

```json
{
  "mcpServers": {
    "google-patents-mcp": {
      "command": "npx",
      "args": ["-y", "@kunihiros/google-patents-mcp"],
      "env": {"SERPAPI_API_KEY": "xxxx"}
    }
  }
}
```

---

## 🚀 功能規格：快速開始

### 方法1: 使用啟動腳本（推薦）

```bash
python run_app.py
```

啟動腳本會自動：
- 檢查並安裝依賴
- 創建必要目錄
- 驗證Claude CLI
- 啟動Web應用

### 方法2: 直接啟動Streamlit

```bash
# 安裝依賴
pip install -r requirements.txt

# 啟動應用
streamlit run patent_drafter_app.py
```

---

## 🔄 執行流程

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
5. 並行起草內容 ←------- A5 (Content Drafting)
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

### 子代理執行順序

各專業子代理必須按以下順序執行：

1. **input-parser** → 解析技術交底書
2. **patent-searcher** → 檢索相似專利
3. **outline-generator** → 生成專利大綱
4. **abstract-drafter** → 起草摘要
5. **claims-drafter** → 起草權利要求書
6. **description-drafter** → 起草說明書 (>10,000字)
7. **diagram-generator** → 生成 Mermaid 圖表
8. **markdown-merger** → 合併所有內容

詳細流程請參考 [CLAUDE.md](../CLAUDE.md)

---

## 📋 功能特性

- 📄 **文件上傳**: 支持DOCX格式技術交底書上傳
- 🤖 **AI驅動**: 使用Claude AI生成專業專利提案
- 📊 **實時日誌**: 流式顯示生成過程的詳細日誌，支持格式化顯示
- ⏯️ **進程控制**: 支持開始、中止、強制清理操作
- 📚 **歷史管理**: 查看和管理歷史會話記錄
- 🔄 **自動刷新**: 運行時自動刷新日誌內容
- 🎛️ **顯示選項**: 支持原始JSON/格式化顯示，行數限制等
- 📊 **狀態監控**: 實時顯示進程和會話狀態

---

## 🛠️ 技術棧

### 核心技術

| 層級 | 技術 | 用途 |
|-----|------|------|
| **AI 引擎** | Claude 3.5 Sonnet | 專利內容生成、分析 |
| **Agent 框架** | Claude Code Agent SDK | 多 Agent 協調 |
| **前端** | Streamlit | Web 使用者介面 |
| **文件處理** | markitdown, python-docx | DOCX 解析 |
| **專利檢索** | Google Patents API (via SERP API) | 專利搜尋 |
| **網頁檢索** | Exa Search API | 技術文件搜尋 |
| **圖表生成** | Mermaid.js | 技術圖表 |
| **資料格式** | JSON, Markdown | 資料交換 |

### 開發工具

- **IDE**: VS Code + Claude Code 擴充套件
- **版本控制**: Git
- **文件格式**: Markdown + Mermaid
- **專案管理**: IDEF0 建模方法論

### 可選的 Web 介面

專案包含一個 **Streamlit Web 應用** (需要 Python):

#### 技術要求

- Python 3.8+
- Streamlit (Web 框架)
- markitdown (文件處理)
- psutil (進程管理)

#### 用途

- 提供友善的檔案上傳介面
- 視覺化顯示生成進度
- 管理多個專案會話

**但核心邏輯仍然是純 Prompt！** Web 介面只是一個可選的使用者介面層。

---

## 📁 目錄結構

```
PatentDrafter/
├── patent_drafter_app.py   # Streamlit應用主文件
├── run_app.py              # 啟動腳本
├── requirements.txt        # Python依賴
├── CLAUDE.md               # Claude Agent 專案指令
├── data/                   # 輸入文件目錄
│   └── 輸入.docx          # 上傳的技術交底書
├── output/                 # 輸出文件目錄
│   ├── {session_id}.log   # 各會話的日誌文件
│   └── temp_*/            # Claude生成的專利文件
│       ├── 01_input/          # 輸入解析結果
│       ├── 02_research/       # 專利檢索結果
│       ├── 03_outline/        # 專利大綱
│       ├── 04_content/        # 專利內容
│       ├── 05_diagrams/       # Mermaid 圖表
│       ├── 06_final/          # 最終輸出
│       └── metadata/          # 執行元數據
└── docs/                   # 開發者文檔
    ├── spec/              # 產品規格（本文檔）
    ├── A0_system_idef0.md # 系統IDEF0架構
    └── troubleshooting/   # 故障排除文檔
```

---

## 📋 資料流轉

### 子代理輸入輸出映射

| 子代理 | 工作目錄 | 輸入文件 | 輸出文件 |
|--------|----------|----------|----------|
| input-parser | 01_input/ | raw_document.docx | parsed_info.json |
| patent-searcher | 02_research/ | parsed_info.json | similar_patents.json, prior_art_analysis.md |
| outline-generator | 03_outline/ | similar_patents.json, parsed_info.json | patent_outline.md, structure_mapping.json |
| abstract-drafter | 04_content/ | patent_outline.md | abstract.md |
| claims-drafter | 04_content/ | patent_outline.md, abstract.md | claims.md |
| description-drafter | 04_content/ | patent_outline.md, claims.md | description.md |
| diagram-generator | 05_diagrams/ | description.md, structure_mapping.json | *.mmd 圖表文件 |
| markdown-merger | 06_final/ | 所有 04_content/ 和 05_diagrams/ | complete_patent.md |

---

## 💡 使用方法

### 1. 啟動應用

```bash
python run_app.py
```

應用將在 http://localhost:8501 打開

### 2. 上傳文件

- 在側邊欄點擊"上傳DOCX文件"
- 選擇您的技術交底書文件
- 系統會自動保存並驗證文件

### 3. 生成專利提案

1. **創建新會話**: 點擊"生成新Session"按鈕
2. **開始生成**: 點擊"開始"按鈕啟動Claude AI
3. **查看日誌**: 主界面會實時顯示生成過程
4. **控制進程**: 可以隨時中止或強制清理進程

### 4. 查看歷史

- 在側邊欄的"歷史Session"區域選擇過往會話
- 支持恢復中斷的會話
- 查看完整的生成日誌

---

## 🎯 品質標準

### 文檔品質要求

- ✅ 嚴格遵循中國《專利法》和《專利審查指南》
- ✅ 具體實施方式章節 > 10,000 字
- ✅ 全文術語一致性 100%
- ✅ 各章節邏輯鏈條完整
- ✅ 所有中間文件保存在工作目錄

### 目錄結構品質要求

- ✅ 100% 符合標準目錄結構
- ✅ 文件放置在正確目錄
- ✅ JSON 文件格式正確可解析
- ✅ Mermaid 圖表語法正確 (.mmd 擴展名)

### 數據完整性要求

- ✅ 每個輸出包含版本號和時間戳
- ✅ 結構化數據包含完整字段驗證
- ✅ 關鍵術語在所有文件中一致
- ✅ 圖表引用與文件名匹配

---

## 🔧 高級功能

### 日誌顯示選項

- **原始JSON**: 顯示Claude的原始輸出格式
- **格式化顯示**: 易讀的格式化日誌內容
- **行數限制**: 控制顯示的日誌行數
- **自動刷新**: 運行時自動更新日誌內容

### 進程管理

- **優雅中止**: 嘗試正常終止Claude進程
- **強制清理**: 終止所有相關的Claude進程
- **狀態監控**: 實時顯示進程狀態和活動狀態

### Session管理

- **自動檢測**: 智能檢測活躍的Session
- **會話恢復**: 支持恢復中斷的會話
- **歷史查看**: 查看所有歷史會話記錄

---

## 🔧 品質保證機制

### 格式驗證

- **JSON 格式檢查** - 由 Claude AI 執行
- **Mermaid 語法檢查** - 使用 `bin/check_mermaid.sh`
- **Markdown 語法** - 標準 CommonMark 規範

### 內容驗證

- **字數要求** - 說明書 > 10,000 字
- **術語一致性** - 全文關鍵術語必須統一
- **邏輯完整性** - 各章節邏輯鏈條完整

### 錯誤恢復

- **最多重試 3 次** - 子 Agent 失敗時自動重試
- **錯誤日誌** - 儲存至 `output/temp_[uuid]/[agent_name]_error.log`
- **版本控制** - 保留多個版本便於回滾
- **Checkpoint 機制** - 重要節點自動建立檢查點

### 子代理執行失敗處理

- 某個子代理失敗時，儲存錯誤日誌到 `output/temp_[uuid]/[agent_name]_error.log`
- 檢查輸入檔案是否存在且格式正確
- 必要時重新執行前置子代理
- 最多重試 3 次，超過後人工介入

### 資料一致性檢查

- 每個子代理完成後驗證輸出檔案完整性
- 關鍵欄位在不同檔案間的一致性檢查
- JSON 格式和 Mermaid 語法驗證
- 檔案大小和基本內容合理性檢查

### 回滾機制

- 保留每個子代理的多個版本輸出
- 發現問題時可回退到上一個穩定版本
- 清理機制: 專案完成後可選擇刪除中間檔案
- 重要節點自動建立 checkpoint

### 監控和日誌

- 每個子代理的執行時間記錄
- 資源使用情況監控
- 關鍵決策點的日誌記錄
- 最終生成專案執行報告

---

## ⚠️ 故障排除

### 常見問題

1. **Claude CLI未找到**
   ```bash
   # 檢查Claude是否安裝
   claude --version

   # 如果未安裝，請參考官方文檔安裝
   # https://docs.anthropic.com/claude/reference/claude-cli
   ```

2. **進程無法中止**
   - 使用"強制清理所有Claude進程"按鈕
   - 或者手動在終端中終止進程

3. **日誌不顯示**
   - 點擊"手動刷新"按鈕
   - 檢查output目錄下是否存在對應的日誌文件
   - 嘗試切換到原始JSON格式查看

4. **文件上傳失敗**
   - 確保文件格式為DOCX
   - 檢查文件大小是否合理（建議<50MB）
   - 確保data目錄有寫入權限

### 警告信息

應用可能會顯示以下警告，這些通常可以忽略：
- `Thread 'Thread-X': missing ScriptRunContext!` - 這是Streamlit多線程環境中的正常警告
- `missing ScriptRunContext! This warning can be ignored when running in bare mode` - 同上

這些警告不影響應用功能，是Streamlit框架的已知行為。

---

## 🎯 使用技巧

1. **最佳實踐**：
   - 上傳完整的、結構清晰的技術交底書
   - 使用具體的Session ID便於後續管理
   - 定期清理舊的日誌文件節省空間

2. **性能優化**：
   - 限制顯示的日誌行數可以提高界面響應速度
   - 在長時間運行時可以使用手動刷新減少資源消耗

3. **調試技巧**：
   - 使用原始JSON格式查看詳細的Claude輸出
   - 檢查狀態詳情瞭解進程和會話的準確狀態

---

## 📞 支持

如果遇到問題：

1. 檢查本文檔的故障排除部分
2. 確認Claude CLI正確安裝和配置
3. 查看終端輸出的詳細錯誤信息
4. 檢查網絡連接和API訪問權限
5. 參考 [docs/troubleshooting/](../troubleshooting/) 中的詳細故障排除指南

---

## 🔒 隱私說明

- 上傳的文件僅在本地處理，不會上傳到外部服務器
- 日誌文件存儲在本地output目錄
- Claude API調用遵循Anthropic的隱私政策
- 建議定期清理包含敏感信息的日誌文件

---

## 🔗 相關文檔

完整的 IDEF0 功能模組設計請參考：

- [A0 - 系統頂層架構](../A0_system_idef0.md) - 系統全貌
- [A1 - 使用者介面管理](../A1_UI_Management_IDEF0.md) - Web UI 設計
- [A2 - 文件解析](../A2_Document_Parsing_IDEF0.md) - DOCX 處理
- [A3 - 專利檢索](../A3_Patent_Search_IDEF0.md) - 檢索 API 整合
- [A4 - 大綱生成](../A4_Outline_Generation_IDEF0.md) - 大綱生成邏輯
- [A5 - 內容起草](../A5_Content_Writing_IDEF0.md) - 專利內容生成
- [A6 - 圖表生成](../A6_Diagram_Generation_IDEF0.md) - Mermaid 圖表
- [A7 - 文件合併](../A7_Document_Merging_IDEF0.md) - 最終文件組裝
- [A8 - 工作流程控制](../A8_Workflow_Control_IDEF0.md) - Agent 協調

技術規範參考：
- [中國專利法](https://www.cnipa.gov.cn/) - 專利起草規範
- [IDEF0 標準](https://en.wikipedia.org/wiki/IDEF0) - 建模方法論
- [Mermaid 文件](https://mermaid.js.org/) - 圖表語法
- [Claude Code 文檔](https://claude.com/claude-code) - AI 開發環境

---

**最後更新**: 2025-10-30  
**文檔版本**: v2.0  
**維護者**: 專案架構團隊

---

## 🚀 功能規格：快速開始

### 方法1: 使用啟動腳本（推薦）

```bash
python run_app.py
```

啟動腳本會自動：
- 檢查並安裝依賴
- 創建必要目錄
- 驗證Claude CLI
- 啟動Web應用

### 方法2: 直接啟動Streamlit

```bash
# 安裝依賴
pip install -r requirements.txt

# 啟動應用
streamlit run patent_drafter_app.py
```

## 📋 功能特性

- 📄 **文件上傳**: 支持DOCX格式技術交底書上傳
- 🤖 **AI驅動**: 使用Claude AI生成專業專利提案
- 📊 **實時日誌**: 流式顯示生成過程的詳細日誌，支持格式化顯示
- ⏯️ **進程控制**: 支持開始、中止、強制清理操作
- 📚 **歷史管理**: 查看和管理歷史會話記錄
- 🔄 **自動刷新**: 運行時自動刷新日誌內容
- 🎛️ **顯示選項**: 支持原始JSON/格式化顯示，行數限制等
- 📊 **狀態監控**: 實時顯示進程和會話狀態

## 🛠️ 系統要求

- Python 3.8+
- Claude CLI工具
- 網絡連接（用於Claude API）

## 📁 目錄結構

```
PatentDrafter/
├── patent_drafter_app.py   # Streamlit應用主文件
├── run_app.py              # 啟動腳本
├── requirements.txt        # Python依賴
├── data/                   # 輸入文件目錄
│   └── 輸入.docx          # 上傳的技術交底書
├── output/                 # 輸出文件目錄
│   ├── {session_id}.log   # 各會話的日誌文件
│   └── temp_*/            # Claude生成的專利文件
└── APP_README.md          # 應用說明文檔
```

## 💡 使用方法

### 1. 啟動應用

```bash
python run_app.py
```

應用將在 http://localhost:8501 打開

### 2. 上傳文件

- 在側邊欄點擊"上傳DOCX文件"
- 選擇您的技術交底書文件
- 系統會自動保存並驗證文件

### 3. 生成專利提案

1. **創建新會話**: 點擊"生成新Session"按鈕
2. **開始生成**: 點擊"開始"按鈕啟動Claude AI
3. **查看日誌**: 主界面會實時顯示生成過程
4. **控制進程**: 可以隨時中止或強制清理進程

### 4. 查看歷史

- 在側邊欄的"歷史Session"區域選擇過往會話
- 支持恢復中斷的會話
- 查看完整的生成日誌

## 🔧 高級功能

### 日誌顯示選項

- **原始JSON**: 顯示Claude的原始輸出格式
- **格式化顯示**: 易讀的格式化日誌內容
- **行數限制**: 控制顯示的日誌行數
- **自動刷新**: 運行時自動更新日誌內容

### 進程管理

- **優雅中止**: 嘗試正常終止Claude進程
- **強制清理**: 終止所有相關的Claude進程
- **狀態監控**: 實時顯示進程狀態和活動狀態

### Session管理

- **自動檢測**: 智能檢測活躍的Session
- **會話恢復**: 支持恢復中斷的會話
- **歷史查看**: 查看所有歷史會話記錄

## ⚠️ 故障排除

### 常見問題

1. **Claude CLI未找到**
   ```bash
   # 檢查Claude是否安裝
   claude --version

   # 如果未安裝，請參考官方文檔安裝
   # https://docs.anthropic.com/claude/reference/claude-cli
   ```

2. **進程無法中止**
   - 使用"強制清理所有Claude進程"按鈕
   - 或者手動在終端中終止進程

3. **日誌不顯示**
   - 點擊"手動刷新"按鈕
   - 檢查output目錄下是否存在對應的日誌文件
   - 嘗試切換到原始JSON格式查看

4. **文件上傳失敗**
   - 確保文件格式為DOCX
   - 檢查文件大小是否合理（建議<50MB）
   - 確保data目錄有寫入權限

### 警告信息

應用可能會顯示以下警告，這些通常可以忽略：
- `Thread 'Thread-X': missing ScriptRunContext!` - 這是Streamlit多線程環境中的正常警告
- `missing ScriptRunContext! This warning can be ignored when running in bare mode` - 同上

這些警告不影響應用功能，是Streamlit框架的已知行為。

## 🎯 使用技巧

1. **最佳實踐**：
   - 上傳完整的、結構清晰的技術交底書
   - 使用具體的Session ID便於後續管理
   - 定期清理舊的日誌文件節省空間

2. **性能優化**：
   - 限制顯示的日誌行數可以提高界面響應速度
   - 在長時間運行時可以使用手動刷新減少資源消耗

3. **調試技巧**：
   - 使用原始JSON格式查看詳細的Claude輸出
   - 檢查狀態詳情瞭解進程和會話的準確狀態

## 📞 支持

如果遇到問題：

1. 檢查本文檔的故障排除部分
2. 確認Claude CLI正確安裝和配置
3. 查看終端輸出的詳細錯誤信息
4. 檢查網絡連接和API訪問權限

## 🔒 隱私說明

- 上傳的文件僅在本地處理，不會上傳到外部服務器
- 日誌文件存儲在本地output目錄
- Claude API調用遵循Anthropic的隱私政策
- 建議定期清理包含敏感信息的日誌文件