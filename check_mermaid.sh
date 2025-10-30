#!/bin/bash
# Mermaid 圖表語法檢查腳本

echo "🔍 檢查專案中的 Mermaid 圖表語法..."
echo "==========================================="

# 找出所有 .md 文件
MD_FILES=$(find . -name "*.md" -not -path "./node_modules/*" -not -path "./.git/*" -not -path "./output/*")

# 計數器
TOTAL_FILES=0
FILES_WITH_MERMAID=0
TOTAL_MERMAID_BLOCKS=0
GRAPH_SYNTAX=0
FLOWCHART_SYNTAX=0
SUBGRAPH_USAGE=0

for file in $MD_FILES; do
    TOTAL_FILES=$((TOTAL_FILES + 1))

    # 檢查文件是否包含 mermaid
    if grep -q '```mermaid' "$file"; then
        FILES_WITH_MERMAID=$((FILES_WITH_MERMAID + 1))

        # 計算 mermaid 區塊數量
        BLOCKS=$(grep -c '```mermaid' "$file")
        TOTAL_MERMAID_BLOCKS=$((TOTAL_MERMAID_BLOCKS + BLOCKS))

        echo ""
        echo "📄 檔案: $file"
        echo "   Mermaid 區塊數: $BLOCKS"

        # 檢查是否使用 graph 語法
        if grep -A1 '```mermaid' "$file" | grep -q "^graph "; then
            GRAPH_COUNT=$(grep -A1 '```mermaid' "$file" | grep -c "^graph ")
            GRAPH_SYNTAX=$((GRAPH_SYNTAX + GRAPH_COUNT))
            echo "   ⚠️  使用 graph 語法: $GRAPH_COUNT 個 (建議改用 flowchart)"
        fi

        # 檢查是否使用 flowchart 語法
        if grep -A1 '```mermaid' "$file" | grep -q "^flowchart "; then
            FLOWCHART_COUNT=$(grep -A1 '```mermaid' "$file" | grep -c "^flowchart ")
            FLOWCHART_SYNTAX=$((FLOWCHART_SYNTAX + FLOWCHART_COUNT))
            echo "   ✅ 使用 flowchart 語法: $FLOWCHART_COUNT 個"
        fi

        # 檢查是否使用 subgraph
        if grep -A50 '```mermaid' "$file" | grep -q "subgraph "; then
            SUBGRAPH_COUNT=$(grep -A50 '```mermaid' "$file" | grep -c "subgraph ")
            SUBGRAPH_USAGE=$((SUBGRAPH_USAGE + SUBGRAPH_COUNT))
            echo "   ⚠️  使用 subgraph: $SUBGRAPH_COUNT 個 (可能導致渲染問題)"
        fi
    fi
done

echo ""
echo "==========================================="
echo "📊 統計總結"
echo "==========================================="
echo "總 Markdown 文件數: $TOTAL_FILES"
echo "包含 Mermaid 的文件: $FILES_WITH_MERMAID"
echo "Mermaid 區塊總數: $TOTAL_MERMAID_BLOCKS"
echo ""
echo "語法使用情況:"
echo "  - graph 語法: $GRAPH_SYNTAX 個 (建議修復)"
echo "  - flowchart 語法: $FLOWCHART_SYNTAX 個 (推薦)"
echo "  - 使用 subgraph: $SUBGRAPH_USAGE 個 (可能有問題)"
echo ""

if [ $GRAPH_SYNTAX -gt 0 ] || [ $SUBGRAPH_USAGE -gt 0 ]; then
    echo "⚠️  發現需要修復的語法！"
    echo ""
    echo "修復建議:"
    echo "1. 將 'graph TB' 改為 'flowchart TB'"
    echo "2. 將 'graph LR' 改為 'flowchart LR'"
    echo "3. 移除或簡化 subgraph 結構"
    echo "4. 參考: docs/Mermaid_故障排除.md"
else
    echo "✅ 所有 Mermaid 圖表語法良好！"
fi

echo ""
echo "==========================================="
