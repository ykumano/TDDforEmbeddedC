/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*
 * Copyright (c) 2007, Michael Feathers, James Grenning and Bas Vodde
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef D_TestOutput_h
#define D_TestOutput_h

///////////////////////////////////////////////////////////////////////////////
//
//  TestOutput.h
//
//  This is a minimal printer inteface.
//  We kept streams out too keep footprint small, and so the test
//  harness could be used with less capable compilers so more
//  platforms could use this test harness
//
///////////////////////////////////////////////////////////////////////////////

class Utest;
class TestFailure;
class TestResult;

class TestOutput
{
public:
	explicit TestOutput();
	virtual ~TestOutput();

	virtual void printTestsStarted();
	virtual void printTestsEnded(const TestResult& result);
	virtual void printCurrentTestStarted(const Utest& test);
	virtual void printCurrentTestEnded(const TestResult& res);
	virtual void printCurrentGroupStarted(const Utest& test);
	virtual void printCurrentGroupEnded(const TestResult& res);

	virtual void verbose();
	virtual void print(const char*)=0;
	virtual void print(long);
	virtual void printDouble(double);
	virtual void printHex(long);
	virtual void print(const TestFailure& failure);
	virtual void printTestRun(int number, int total);
	virtual void setProgressIndicator(const char*);

	virtual void flush();

private:

	virtual void printProgressIndicator();
	void printFileAndLineForTestAndFailure(const TestFailure& failure);
	void printFileAndLineForFailure(const TestFailure& failure);
	void printFailureInTest(SimpleString testName);
	void printFailureMessage(SimpleString reason);
	void printEclipseErrorInFileOnLine(SimpleString testFile, int lineNumber);

	TestOutput(const TestOutput&);
	TestOutput& operator=(const TestOutput&);

	int dotCount_;
	bool verbose_;
	const char* progressIndication_;
};

TestOutput& operator<<(TestOutput&, const char*);
TestOutput& operator<<(TestOutput&, long);

///////////////////////////////////////////////////////////////////////////////
//
//  ConsoleTestOutput.h
//
//  Printf Based Solution
//
///////////////////////////////////////////////////////////////////////////////

class ConsoleTestOutput: public TestOutput
{
public:
	explicit ConsoleTestOutput()
	{
	}
	;
	virtual ~ConsoleTestOutput()
	{
	}
	;

	virtual void print(const char* s);
	virtual void flush();

private:
	ConsoleTestOutput(const ConsoleTestOutput&);
	ConsoleTestOutput& operator=(const ConsoleTestOutput&);
};

///////////////////////////////////////////////////////////////////////////////
//
//  StringBufferTestOutput.h
//
//  TestOutput for test purposes
//
///////////////////////////////////////////////////////////////////////////////


class StringBufferTestOutput: public TestOutput
{
public:
	explicit StringBufferTestOutput()
	{
	}
	;
	virtual ~StringBufferTestOutput()
	{
	}
	;

	void print(const char* s)
	{
		output += s;
	}

	void flush()
	{
		output = "";
	}

	const SimpleString& getOutput()
	{
		return output;
	}

private:
	SimpleString output;

	StringBufferTestOutput(const StringBufferTestOutput&);
	StringBufferTestOutput& operator=(const StringBufferTestOutput&);

};

#endif  // D_TestOutput_h
