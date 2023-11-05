// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
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

#include "CUTimer.h"

#include <sys/timeb.h>
#include <time.h>

#include <iostream>

#pragma optimize("", off)

NS_CU_BEGIN

uint64_t Timer::GetTimeSecond()
{
	timeb t;
	ftime(&t); // Get ms time
	return t.time;
}

/// YYYY-MM-DD HH:mm:ss		
const char* Timer::SecondTime2Str(uint64_t timestamp, const char* format)
{
	time_t tim = (time_t)timestamp;
	struct tm t = *localtime(&tim);
	char tim_str[100];
	std::string tim_fmt;
	if (format == "YYYYMMDD-HHmmss") {
		strftime(tim_str, sizeof(tim_str), "%Y%m%d-%H%M%S", &t);
		tim_fmt = tim_str;
	}
	else {
		// format == "YYYY-MM-DD HH:mm:ss"
		strftime(tim_str, sizeof(tim_str), "%Y-%m-%d %H:%M:%S", &t);
		tim_fmt = tim_str;
	}
	return tim_fmt.c_str();
}

uint64_t Timer::GetTimeMicroSecond()
{
	timeb t;
	ftime(&t); // Get ms time
	return t.time*1000 + t.millitm;
}

NS_CU_END

#pragma optimize("", on)
