// MIT License
//
// Copyright (c) 2021~2023 [coder4869](https://github.com/coder4869)
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

#ifndef QTPRACTICAL_DEF_H
#define QTPRACTICAL_DEF_H

#define NS_QPRAC_BEGIN namespace QPRAC {
#define NS_QPRAC_END	} //namespace QPRAC

#ifdef QTPRACTICAL_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPRACTICAL_CLASS __declspec(dllexport)
#		define QTPRACTICAL_API extern "C" __declspec(dllexport)
#	else
#		define QTPRACTICAL_CLASS __attribute__((externally_visible))
#		define QTPRACTICAL_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPRACTICAL_CLASS __declspec(dllimport)
#		define QTPRACTICAL_API extern "C" __declspec(dllimport)
#	else
#		define QTPRACTICAL_CLASS __attribute__((externally_visible))
#		define QTPRACTICAL_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTPRACTICAL_EXPORT

#endif /* QTPRACTICAL_DEF_H */
