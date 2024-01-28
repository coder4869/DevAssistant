// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifdef WIN
// 无警告编号
#pragma warning(disable: 4619)

// xxx隐式定义为“已删除”
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
#pragma warning(disable: 5026)
#pragma warning(disable: 5027)
#pragma warning(disable: 4457)

// 内联函数
#pragma warning(disable: 4514)
#pragma warning(disable: 4710)
#pragma warning(disable: 4711)

// 数据类型转换
#pragma warning(disable: 4100)
#pragma warning(disable: 4820)  // 字节填充
#pragma warning(disable: 4365)  // 有符号/无符号不匹配
#pragma warning(disable: 4388)  // 有符号/无符号不匹配
#pragma warning(disable: 4267)
#pragma warning(disable: 5219)
#pragma warning(disable: 4946)
#pragma warning(disable: 5243)
#pragma warning(disable: 4242)

#pragma warning(disable: 5045)
#pragma warning(disable: 4668)
#pragma warning(disable: 4464)
#pragma warning(disable: 5039)
#pragma warning(disable: 5240) // 特性在此语法位置被忽略

#pragma warning(disable: 4710) 
#pragma warning(disable: 4577) 

#endif // WIN


#ifdef WIN
#	define API_EXPORT _declspec(dllexport)
#	define API_IMPORT _declspec(dllimport)
#else // Linux
#	define API_EXPORT __attribute__((visibility("default")))
#	define API_IMPORT 
#endif // Linux


#ifndef CCK_DEFINE_H
#define CCK_DEFINE_H

//#ifdef WIN
//const char* PATH_SPLIT_TAG = "\\";
//#else // Linux
//const char* PATH_SPLIT_TAG = "/";
//#endif // Linux

#endif // CCK_DEFINE_H
