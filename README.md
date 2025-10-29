# 專利寫作智能體


```bash
# 安裝 Claude code
npm install -g @anthropic-ai/claude-code

# 安裝其他依賴
pip install -r requirements.txt

# 配置環境變量
cp .mcp.json.example .mcp.json
cp .claude/settings.local.json.example .claude/settings.local.json

# 修改 .mcp.json 中的 API KEY，包括SERPAPI_API_KEY和EXA_API_KEY
# 修改 .claude/settings.local.json 中的 Token 和 URL（配置為第三方模型，如果不使用第三方，刪除掉以ANTHROPIC開頭的env即可）

#CLI
claude --dangerously-skip-permissions "根據 data/輸入.docx 編寫專利提案 " -p  --output-format stream-json --verbose

output/temp_9ba0a678-5210-42e0-8f52-31b47bf630f6 為示例輸出

```

### Workflow 設計

```mermaid
graph TD
    subgraph "輸入與準備階段"
        A(用戶輸入: 技術資料) --> B[Input Parser: 解析關鍵技術點];
        B --> C[Patent Searcher: 檢索現有技術];
        subgraph "工具節點"
            %% --- 增加的工具節點 ---
            C --> C1[工具: 專利搜索]
            C --> C2[工具: 論文搜索]
            %% --- 結束 ---
        end
        B --> D[Outline Generator: 生成專利大綱];
        
        %% --- 增加循環 ---
        C1 -- "重複" --> C;
        C2 -- "重複" --> C;
    end

    subgraph "核心撰寫與輸出"
        E[Claims Writer: 撰寫權利要求]
        F[Description Writer: 撰寫具體實施方式]
        
        subgraph "並行生成"
            direction LR
            G[Diagram Generator: 生成附圖/流程圖]
            H[Abstract Writer: 撰寫摘要]
        end

        I[Markdown Merger: 合併所有部分]
        J(輸出: 完整專利草稿.md)

        %% --- 內部流向 ---
        E --> F
        F --> G
        F -- "提供素材" --> H
        E -- "提供保護範圍" --> H
        
        %% --- 匯合 ---
        E --> I
        F --> I
        G --> I
        H --> I
        
        I --> J
    end

    %% --- 跨子圖鏈接 ---
    C -- "提供參考資料" --> E;
    D -- "提供文檔結構" --> E;
    C -- "提供參考資料" --> F;

    %% 樣式
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px;
    classDef input fill:#E0F7FA,stroke:#00796B;
    classDef output fill:#FFECB3,stroke:#FFA000;
    
    class A,J input;
    class B,C,D,E,F,G,H,I,C1,C2 output;
```
