# 專案目錄結構說明

## 📁 整體結構

```
PatentWriterAgent/
├── .claude/                     # Claude Code Agent 配置
│   ├── agents/                  # 8 個子 Agent 配置檔
│   │   ├── abstract-writer.md
│   │   ├── claims-writer.md
│   │   ├── description-writer.md
│   │   ├── diagram-generator.md
│   │   ├── input-parser.md
│   │   ├── markdown-merger.md
│   │   ├── outline-generator.md
│   │   └── patent-searcher.md
│   └── settings.local.json      # 本地設定（不提交）
│
├── docs/                        # ✨ 功能設計文件
│   ├── README.md                # 功能設計導覽
│   ├── A0_system_idef0.md       # 系統頂層架構
│   ├── A1_UI_Management_IDEF0.md
│   ├── A2_Document_Parsing_IDEF0.md
│   ├── A3_Patent_Search_IDEF0.md
│   ├── A4_Outline_Generation_IDEF0.md
│   ├── A5_Content_Writing_IDEF0.md
│   ├── A6_Diagram_Generation_IDEF0.md
│   ├── A7_Document_Merging_IDEF0.md
│   ├── A8_Workflow_Control_IDEF0.md
│   └── troubleshooting/         # 🔧 開發除錯記錄
│       ├── README.md            # 除錯記錄說明
│       ├── Mermaid_最終解決方案.md
│       ├── Mermaid_使用指南.md
│       ├── Mermaid_故障排除.md
│       ├── Mermaid_擴充套件切換指南.md
│       ├── Mermaid_快速測試.md
│       └── Mermaid_測試.md
│
├── data/                        # 範例資料
│   ├── example_patent.md        # 範例專利文件
│   └── 輸入.docx                # 範例技術交底書
│
├── output/                      # 執行輸出目錄
│   └── temp_[uuid]/             # 每次執行的工作目錄
│       ├── 01_input/
│       ├── 02_research/
│       ├── 03_outline/
│       ├── 04_content/
│       ├── 05_diagrams/
│       ├── 06_final/
│       └── metadata/
│
├── CLAUDE.md                    # 主 Agent 專案管理指令
├── PATENT_SKILL.md              # 專利撰寫技能指南
├── README.md                    # 專案主文件
├── 專案說明.md                  # 專案詳細說明
├── arch.md                      # 系統架構圖
├── APP_README.md                # Streamlit 應用說明
├── check_mermaid.sh             # Mermaid 語法檢查腳本
├── convert_to_traditional.py   # 簡繁轉換工具
├── app.py                       # Streamlit UI（可選）
├── requirements.txt             # Python 依賴
├── .mcp.json                    # MCP 伺服器配置
└── .gitignore
```

---

## 🎯 目錄組織原則

### `docs/` - 功能設計文件

**用途**：存放專案功能架構、系統設計、IDEF0 建模文件

**內容**：
- ✅ IDEF0 架構設計（A0-A8）
- ✅ 系統功能規格
- ✅ 模組介面定義
- ✅ 資料流程設計
- ✅ 技術實作規劃

**適合角色**：
- 專案管理者
- 系統架構師
- 功能開發者
- 新成員了解專案

---

### `docs/troubleshooting/` - 開發除錯記錄

**用途**：記錄開發過程中遇到的問題、診斷過程和解決方案

**內容**：
- ✅ 工具使用問題
- ✅ 環境配置問題
- ✅ 擴充套件相容性問題
- ✅ 除錯步驟記錄
- ✅ 解決方案和最佳實踐

**適合角色**：
- 遇到類似問題的開發者
- 負責維護開發環境的工程師
- 需要了解已知限制的團隊成員

**維護政策**：
- 問題解決後歸檔到 `troubleshooting/archived/`
- 定期檢視是否仍然相關
- 持續更新解決方案

---

### `.claude/` - AI Agent 配置

**用途**：Claude Code Agent SDK 的配置和子 Agent 定義

**內容**：
- ✅ 8 個專業子 Agent 的 Prompt 定義
- ✅ Agent 執行參數設定
- ✅ 本地環境設定

**特點**：
- 純 Prompt Engineering（0 行程式碼）
- 每個子 Agent 獨立的 Markdown 配置
- 透過 CLAUDE.md 主 Agent 協調

---

### `data/` - 範例資料

**用途**：提供測試和示範用的範例資料

**內容**：
- ✅ 範例技術交底書（DOCX）
- ✅ 範例專利文件（Markdown）

---

### `output/` - 執行輸出

**用途**：存放每次專利生成的完整工作目錄

**結構**：每個 UUID 目錄包含 8 個階段的輸出
- `01_input/` - 輸入解析結果
- `02_research/` - 專利檢索結果
- `03_outline/` - 大綱生成結果
- `04_content/` - 內容撰寫結果
- `05_diagrams/` - 圖表生成結果
- `06_final/` - 最終合併文件
- `metadata/` - 執行日誌和元資料

**特點**：
- 不納入 Git 版本控制（在 .gitignore 中）
- 保留完整的執行追蹤
- 便於除錯和品質檢查

---

## 📝 文件命名規範

### IDEF0 架構文件

```
A[層級編號]_[模組名稱]_IDEF0.md

範例：
- A0_system_idef0.md          （頂層系統架構）
- A1_UI_Management_IDEF0.md   （UI 管理模組）
- A2_Document_Parsing_IDEF0.md（文件解析模組）
```

### 除錯記錄文件

```
[工具名稱]_[問題類型].md

範例：
- Mermaid_故障排除.md
- VSCode_擴充套件問題.md
- API_連線逾時解決方案.md
```

### Agent 配置文件

```
[agent功能]-[writer/generator/parser/etc].md

範例：
- abstract-writer.md
- claims-writer.md
- input-parser.md
```

---

## 🔄 文件維護流程

### 新增功能設計

1. 在 `docs/` 中建立新的 IDEF0 文件
2. 更新 `docs/A0_system_idef0.md` 加入新模組
3. 更新 `docs/README.md` 的導覽章節
4. 提交 Git 並說明新增原因

### 記錄除錯問題

1. 在 `docs/troubleshooting/` 建立除錯文件
2. 遵循除錯文件結構模板
3. 更新 `docs/troubleshooting/README.md`
4. 提交 Git 並標註問題類型

### 歸檔已解決問題

1. 確認問題已在上游修復或不再相關
2. 移動到 `docs/troubleshooting/archived/`
3. 在 `troubleshooting/README.md` 記錄歸檔原因
4. 提交 Git

---

## 🚀 快速導覽

### 我想了解系統架構
👉 從 [`docs/README.md`](docs/README.md) 開始

### 我遇到開發問題
👉 查看 [`docs/troubleshooting/README.md`](docs/troubleshooting/README.md)

### 我想使用這個專案
👉 閱讀 [`README.md`](README.md) 和 [`專案說明.md`](專案說明.md)

### 我要開發新功能
👉 參考 [`docs/A0_system_idef0.md`](docs/A0_system_idef0.md) 了解架構

### 我要設定 Agent
👉 查看 [`CLAUDE.md`](CLAUDE.md) 和 `.claude/agents/`

---

## 📊 專案統計

**截至 2025-10-30**

| 類別 | 數量 | 說明 |
|-----|------|------|
| IDEF0 設計文件 | 10 個 | A0 + A1-A8 + README |
| 除錯記錄文件 | 7 個 | Mermaid 相關 + README |
| Agent 配置文件 | 8 個 | 專業子 Agent |
| Mermaid 圖表 | 77 個 | 分布在 16 個文件中 |
| 功能模組 | 8 個 | 完整的 ICOM 分析 |
| 子功能 | 32 個 | 每個模組 4 個子功能 |

---

## 🎓 學習路徑

### 第一週：了解專案
1. 閱讀 [README.md](README.md)
2. 閱讀 [專案說明.md](專案說明.md)
3. 查看 [docs/A0_system_idef0.md](docs/A0_system_idef0.md)
4. 執行範例產生專利文件

### 第二週：深入架構
1. 詳讀所有 IDEF0 文件（A1-A8）
2. 了解各模組的 ICOM 關係
3. 研究 Agent 配置檔案
4. 嘗試修改 Agent Prompt

### 第三週：開發實作
1. 選擇一個模組進行改進
2. 參考 IDEF0 設計實作功能
3. 記錄遇到的問題到 troubleshooting/
4. 更新相關設計文件

---

**最後更新**：2025-10-30
**維護者**：專案團隊
