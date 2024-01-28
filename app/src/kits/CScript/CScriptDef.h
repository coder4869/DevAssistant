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

#ifndef CSCRIPT_DEF_H
#define CSCRIPT_DEF_H

#define NS_CS_BEGIN namespace CS {
#define NS_CS_END	} //namespace CS

#ifdef CSCRIPT_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CSCRIPT_CLASS __declspec(dllexport)
#		define CSCRIPT_API extern "C" __declspec(dllexport)
#	else
#		define CSCRIPT_CLASS __attribute__((externally_visible))
#		define CSCRIPT_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CSCRIPT_CLASS __declspec(dllimport)
#		define CSCRIPT_API extern "C" __declspec(dllimport)
#	else
#		define CSCRIPT_CLASS __attribute__((externally_visible))
#		define CSCRIPT_API extern "C" __attribute__((externally_visible))
#	endif

#endif // CSCRIPT_EXPORT

#endif /* CSCRIPT_DEF_H */
