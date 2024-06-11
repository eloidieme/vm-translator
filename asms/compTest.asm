	// push constant 17
	@17
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1

	// push constant 17
	@17
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1

	// eq
	@SP
	A=M-1
	D=M
	@SP
	M=M-1
	A=M-1
	D=M-D
	@EQUAL.0
	D;JEQ
	@SP
	A=M-1
	M=0
	@NOTEQUAL.0
	0;JMP
	(EQUAL.0)
	@SP
	A=M-1
	M=-1
	(NOTEQUAL.0)
