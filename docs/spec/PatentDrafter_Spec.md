# 專利提案生成器 - Streamlit Web應用

這是一個基於Streamlit的Web應用，用於生成專利提案。用戶可以上傳DOCX文件，調用Claude AI進行專利提案的生成，並實時查看生成過程的日誌。

## 🚀 快速開始

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
streamlit run patent_writer_app.py
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
PatentWriterLocal/
├── patent_writer_app.py    # Streamlit應用主文件
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