#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
簡體中文轉繁體中文轉換腳本
使用 OpenCC 進行轉換，保留專有名詞
"""
import opencc
import sys
import re

def convert_file(input_file, output_file=None):
    """
    將簡體中文檔案轉換為繁體中文

    Args:
        input_file: 輸入檔案路徑
        output_file: 輸出檔案路徑（如果為 None，則覆蓋原檔案）
    """
    # 初始化 OpenCC 轉換器（簡體轉繁體）
    # 使用 's2t' 配置（簡體轉繁體）
    converter = opencc.OpenCC('s2t')

    # 讀取檔案內容
    with open(input_file, 'r', encoding='utf-8') as f:
        content = f.read()

    # 專有名詞保護列表（這些詞不應該被轉換）
    protected_terms = [
        'HTTP', 'HTTPS', 'BitTorrent', 'JSON', 'API', 'REST', 'WebSocket',
        'TCP', 'UDP', 'IP', 'DNS', 'CDN', 'P2P', 'DHT', 'GPS', 'NAT',
        'MySQL', 'PostgreSQL', 'TiDB', 'CockroachDB', 'FTP',
        'gzip', 'Range', 'GET', 'POST', 'HEAD', 'Tracker', 'Seed', 'peer',
        'torrent', 'GitHub', 'mermaid', 'Mermaid'
    ]

    # 轉換內容
    converted_content = converter.convert(content)

    # 輸出檔案路徑
    if output_file is None:
        output_file = input_file

    # 寫入轉換後的內容
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(converted_content)

    print(f"[SUCCESS] Converted: {input_file}")
    if output_file != input_file:
        print(f"  Output to: {output_file}")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python convert_to_traditional.py <input_file> [output_file]")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else None

    convert_file(input_file, output_file)
