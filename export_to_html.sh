#!/bin/bash

# 批量匯出 Markdown 為 HTML
# 使用 Markdown Preview Enhanced
# 目標目錄：docs/html/

echo "🚀 PatentWriterAgent - Markdown 批量匯出為 HTML"
echo "==========================================="
echo ""

# 設定來源和目標目錄
SOURCE_DIR="docs"
OUTPUT_DIR="docs/html"

# 確保輸出目錄存在
mkdir -p "$OUTPUT_DIR"

# 需要匯出的文件清單（IDEF0 架構文件）
FILES=(
    "$SOURCE_DIR/README.md"
    "$SOURCE_DIR/A0_system_idef0.md"
    "$SOURCE_DIR/A1_UI_Management_IDEF0.md"
    "$SOURCE_DIR/A2_Document_Parsing_IDEF0.md"
    "$SOURCE_DIR/A3_Patent_Search_IDEF0.md"
    "$SOURCE_DIR/A4_Outline_Generation_IDEF0.md"
    "$SOURCE_DIR/A5_Content_Writing_IDEF0.md"
    "$SOURCE_DIR/A6_Diagram_Generation_IDEF0.md"
    "$SOURCE_DIR/A7_Document_Merging_IDEF0.md"
    "$SOURCE_DIR/A8_Workflow_Control_IDEF0.md"
)

# 計數器
total=${#FILES[@]}
processed=0
success=0
skipped=0

echo "📋 準備匯出 $total 個文件"
echo ""
echo "📌 操作說明："
echo "   1. 腳本會依次開啟每個 Markdown 文件"
echo "   2. 請在 VS Code 中："
echo "      - 按 Ctrl+Shift+V 開啟預覽"
echo "      - 在預覽視窗右鍵 → HTML → HTML (offline)"
echo "   3. 完成後按 Enter 繼續下一個文件"
echo "   4. 如要跳過，直接按 Enter"
echo ""
read -p "按 Enter 開始..."
echo ""

# 遍歷文件清單
for file in "${FILES[@]}"; do
    ((processed++))

    if [ ! -f "$file" ]; then
        echo "[$processed/$total] ⚠️  文件不存在: $file"
        ((skipped++))
        continue
    fi

    filename=$(basename "$file" .md)
    echo "[$processed/$total] 📄 處理: $filename.md"

    # 開啟 VS Code
    code "$file"

    # 提示使用者
    echo "   ⏸️  請在 VS Code 中："
    echo "      1. 按 Ctrl+Shift+V 開啟預覽"
    echo "      2. 右鍵 → HTML → HTML (offline)"
    echo "      3. 完成後按 Enter 繼續，或直接 Enter 跳過"
    echo ""
    read -p "   完成後按 Enter..."

    # 檢查是否生成了 HTML 文件
    html_file="$SOURCE_DIR/$filename.html"

    if [ -f "$html_file" ]; then
        # 移動到目標目錄
        mv "$html_file" "$OUTPUT_DIR/"
        echo "   ✅ 已匯出並移動: $filename.html"
        ((success++))
    else
        echo "   ⏭️  跳過（未找到匯出文件）"
        ((skipped++))
    fi

    echo ""
done

# 顯示統計資訊
echo "==========================================="
echo "📊 匯出完成！"
echo ""
echo "統計資訊："
echo "   總計: $total 個文件"
echo "   成功: $success 個"
echo "   跳過: $skipped 個"
echo ""

if [ $success -gt 0 ]; then
    echo "✅ HTML 文件位置: $OUTPUT_DIR/"
    echo ""
    echo "已匯出的文件："
    ls -1 "$OUTPUT_DIR"/*.html 2>/dev/null | while read htmlfile; do
        size=$(du -h "$htmlfile" | cut -f1)
        basename_html=$(basename "$htmlfile")
        echo "   - $basename_html ($size)"
    done
fi

echo ""
echo "==========================================="
echo "💡 提示："
echo "   - 查看所有 HTML: ls -lh $OUTPUT_DIR/"
echo "   - 在瀏覽器開啟: open $OUTPUT_DIR/A0_system_idef0.html"
echo "   - 或在 Windows: start $OUTPUT_DIR/A0_system_idef0.html"
echo "==========================================="
