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
// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 16
@16
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
@EQUAL.1
D;JEQ
@SP
A=M-1
M=0
@NOTEQUAL.1
0;JMP
(EQUAL.1)
@SP
A=M-1
M=-1
(NOTEQUAL.1)
// push constant 16
@16
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
@EQUAL.2
D;JEQ
@SP
A=M-1
M=0
@NOTEQUAL.2
0;JMP
(EQUAL.2)
@SP
A=M-1
M=-1
(NOTEQUAL.2)
// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
D=M-D
@LT.3
D;JLT
@SP
A=M-1
M=0
@NOTLT.3
0;JMP
(LT.3)
@SP
A=M-1
M=-1
(NOTLT.3)
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
D=M-D
@LT.4
D;JLT
@SP
A=M-1
M=0
@NOTLT.4
0;JMP
(LT.4)
@SP
A=M-1
M=-1
(NOTLT.4)
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
D=M-D
@LT.5
D;JLT
@SP
A=M-1
M=0
@NOTLT.5
0;JMP
(LT.5)
@SP
A=M-1
M=-1
(NOTLT.5)
// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
D=M-D
@GT.6
D;JGT
@SP
A=M-1
M=0
@NOTGT.6
0;JMP
(GT.6)
@SP
A=M-1
M=-1
(NOTGT.6)
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
D=M-D
@GT.7
D;JGT
@SP
A=M-1
M=0
@NOTGT.7
0;JMP
(GT.7)
@SP
A=M-1
M=-1
(NOTGT.7)
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
D=M-D
@GT.8
D;JGT
@SP
A=M-1
M=0
@NOTGT.8
0;JMP
(GT.8)
@SP
A=M-1
M=-1
(NOTGT.8)
// push constant 57
@57
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 53
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
M=D+M
// push constant 112
@112
D=A
@SP
A=M
M=D
@SP
M=M+1
// sub
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
M=M-D
// neg
@SP
A=M-1
M=-M
// and
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
M=D&M
// push constant 82
@82
D=A
@SP
A=M
M=D
@SP
M=M+1
// or
@SP
A=M-1
D=M
@SP
M=M-1
A=M-1
M=D|M
// not
@SP
A=M-1
M=!M
(END)
@END
0;JMP
