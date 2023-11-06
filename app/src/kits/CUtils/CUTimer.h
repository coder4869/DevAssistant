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

// https://blog.csdn.net/weixin_45525272/article/details/109687419

#ifndef CU_TIMER_H
#define CU_TIMER_H

#include <stdint.h>
#include "CUtilsDef.h"

NS_CU_BEGIN
namespace Timer {

	/// @breif Get Time In Second
	uint64_t GetTimeSecond();

	/// @breif second to string time. e.g. 1699158041 to 2023-11-05 12:20:41
	/// @param timestamp	input timestamp in second. e.g. 1699158041
	/// @param format		output date format. supports: 
	///		YYYY-MM-DD HH:mm:ss		YYYYMMDD-HHmmss
	/// @return timestamp in target fmt.
	const char* SecondTime2Str(uint64_t timestamp, const char* format = "YYYY-MM-DD HH:mm:ss");

	/// @breif Get Time In Micro-Second
	uint64_t GetTimeMicroSecond();

} // namespace Timer
NS_CU_END


#endif // CU_TIMER_H
