# 專利起草助手 (PatentDrafter)

基於 Claude AI 的專利申請文件自動生成系統，採用**多 Agent 協作架構**，將複雜的專利起草任務分解為多個專業子任務，由不同的專業 Agent 按順序完成。

## 📌 專案特色

- 🤖 **AI 驅動** - 採用 Claude 3.5 Sonnet 進行專利內容生成
- 🔄 **多 Agent 協作** - 8 個專業子 Agent 流水線式協作
- 📋 **符合規範** - 嚴格遵循中國《專利法》和《專利審查指南》
- 🎯 **專業分工** - 每個 Agent 專注單一任務，提高輸出品質
- 📊 **完整輸出** - 自動生成摘要、權利要求書、說明書、技術圖表
- 🌐 **雙介面** - 支援 CLI 命令行和 Web 應用兩種使用方式

## 🎯 適用場景

- ✅ **發明專利申請** - 技術方案完整，需要詳細說明書
- ✅ **實用新型專利** - 結構創新，需要大量附圖
- ✅ **批次專利起草** - 可並行處理多個專案
- ✅ **專利品質提升** - 學習已有專利的優秀寫作風格

> ⚠️ **重要提醒**: 系統生成的專利文件需由專業專利代理人審查，AI 無法完全替代人工專業判斷。

## 🚀 快速開始

### 1. 環境安裝

```bash
# 安裝 Claude Code (CLI 使用)
npm install -g @anthropic-ai/claude-code

# 安裝 Python 依賴
pip install -r requirements.txt
```

### 2. 配置環境

```bash
# 複製配置範本
cp .mcp.json.example .mcp.json
cp .claude/settings.local.json.example .claude/settings.local.json

# 編輯 .mcp.json 設定 API Keys:
# - SERPAPI_API_KEY (專利檢索)
# - EXA_API_KEY (文獻搜索)

# 編輯 .claude/settings.local.json 設定 Claude API
```

### 3. 開始使用

#### 方法 1: Web 應用 (推薦)

```bash
python run_app.py
```

瀏覽器將自動開啟 http://localhost:8501

#### 方法 2: 命令行

```bash
claude --dangerously-skip-permissions "根據 data/輸入.docx 編寫專利提案" -p --output-format stream-json --verbose
```

---

## 📋 主要功能

### Web 應用功能

- 📄 **文件上傳** - 支持 DOCX 格式技術交底書
- 🤖 **智能生成** - 自動生成完整專利申請文件
- 📊 **實時監控** - 流式顯示生成過程和詳細日誌
- ⏯️ **進程控制** - 開始、暫停、中止操作
- 📚 **歷史管理** - 查看和恢復歷史會話
- 🔄 **自動刷新** - 實時更新執行狀態

### 生成內容

系統會自動生成完整的專利申請文件，包括：

- ✍️ **摘要** - 符合專利法規範的技術摘要
- 📜 **權利要求書** - 多級權利要求保護範圍
- 📖 **說明書** - 詳細技術實施方式 (>10,000字)
- 📊 **技術圖表** - 自動生成流程圖、架構圖、時序圖
- 🔍 **現有技術分析** - 相似專利檢索和比對

---

## 📁 輸出結構

每次執行會在 `output/temp_[uuid]/` 建立以下目錄：

```
output/temp_[uuid]/
├── 01_input/         # 解析後的技術資訊
├── 02_research/      # 專利檢索結果
├── 03_outline/       # 專利文件大綱
├── 04_content/       # 生成的專利內容
│   ├── abstract.md       # 摘要
│   ├── claims.md         # 權利要求書
│   └── description.md    # 說明書
├── 05_diagrams/      # Mermaid 技術圖表
└── 06_final/         # 完整專利文件
    └── complete_patent.md
```

範例輸出: `output/temp_9ba0a678-5210-42e0-8f52-31b47bf630f6/`

---

## 💡 使用說明

### Web 應用操作流程

1. **啟動應用** - 執行 `python run_app.py`
2. **上傳文件** - 在側邊欄上傳 DOCX 技術交底書
3. **生成專利** - 點擊「生成新 Session」→「開始」
4. **查看進度** - 實時查看生成日誌和狀態
5. **下載結果** - 從 `output/temp_[uuid]/06_final/` 取得完整文件

### 最佳實踐

- ✅ 準備結構完整的技術交底書 (建議 < 50MB)
- ✅ 使用有意義的 Session ID 便於管理
- ✅ 定期清理舊的輸出目錄節省空間
- ✅ 使用格式化顯示模式查看日誌更易讀

詳細操作說明請參考 [docs/spec/PatentDrafter_Spec.md](docs/spec/PatentDrafter_Spec.md)

---

## 📊 Mermaid 圖表預覽

本專案文檔和生成的專利文件包含大量 Mermaid 圖表，推薦使用：

### VS Code 預覽 (推薦)

```bash
# 安裝擴充套件
code --install-extension vstirbu.vscode-mermaid-preview

# 使用方式
# 1. 游標放在 Mermaid 程式碼塊中
# 2. Ctrl+Shift+P → "Mermaid: Preview Diagram"
```

### 線上預覽

訪問 https://mermaid.live/ 貼上程式碼即可預覽

詳細說明: [Mermaid 使用指南](docs/troubleshooting/Mermaid_最終解決方案.md)

---

## ⚠️ 故障排除

### 常見問題

**1. Claude CLI 未找到**
```bash
claude --version  # 檢查是否安裝
npm install -g @anthropic-ai/claude-code  # 重新安裝
```

**2. Web 應用無法啟動**
- 確認 Python 3.8+ 已安裝
- 檢查 requirements.txt 依賴是否完整安裝
- 查看終端錯誤訊息

**3. 文件上傳失敗**
- 確保文件格式為 DOCX
- 檢查 data/ 目錄寫入權限
- 檔案大小建議 < 50MB

**4. 進程卡住無回應**
- 使用「強制清理所有 Claude 進程」按鈕
- 或手動終止 Claude 相關進程

**5. Mermaid 圖表無法顯示**
- 參考上方「Mermaid 圖表預覽」章節
- 使用推薦的 VS Code 擴充套件

更多問題請查看 [故障排除文檔](docs/troubleshooting/)

---

## 🛠️ 系統要求

- Python 3.8+
- Node.js 16+ (用於 Claude CLI)
- 網絡連接 (用於 API 調用)
- 8GB+ RAM (建議)

---

## 📚 開發者文檔

技術實作細節請參考 [docs/](docs/) 目錄：

- [系統架構設計](docs/A0_system_idef0.md) - IDEF0 架構圖
- [模組功能文檔](docs/README.md) - 各模組詳細設計
- [故障排除記錄](docs/troubleshooting/) - 開發除錯經驗

---

## 🔒 隱私說明

- 所有文件在本機處理，不上傳至外部伺服器
- 日誌存儲在本機 `output/` 目錄
- API 調用遵循 Anthropic 隱私政策
- 建議定期清理包含敏感資訊的輸出文件

---

## 🤝 支援

遇到問題請依序檢查：

1. 本文檔「故障排除」章節
2. [docs/spec/PatentDrafter_Spec.md](docs/spec/PatentDrafter_Spec.md) 詳細說明
3. [開發者文檔](docs/) 技術細節
4. 終端錯誤訊息和日誌文件
