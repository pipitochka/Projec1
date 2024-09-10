section .data
    
q1 dq 2.0    
q2 dq -2.0
q3 dq 8.0
q4 dq 5.0
q5 dq -5.0
q6 dq 3.0
q7 dq -1.0
q8 dq -3.0

section .text
global f1
global f2
global f3
global df1
global df2
global df3
global test1
global test2
global test3
global dtest1
global dtest2
global dtest3
    
f1: ;  e^x+2
    push ebp
    mov ebp, esp    

    finit
	fld qword [ebp+8]
	fldl2e
	fmulp st1,st0      
	fld1
	fscale             
	fxch
	fld1
	fxch                
	fprem               
	f2xm1              
	faddp        
	fmulp 
    fld qword[q1]
	faddp

    leave
    ret

df1: ; 
    push ebp
    mov ebp, esp

    finit
	fld qword [ebp+8]
	fldl2e
	fmulp st1,st0      
	fld1
	fscale             
	fxch
	fld1
	fxch                
	fprem               
	f2xm1              
	faddp        
	fmulp
     
    leave
    ret

f2: ;-2x+8
    push ebp
    mov ebp, esp

    finit
    fld qword[q2]
    fld qword[ebp+8]
    fmulp
    fld qword[q3]
    faddp

    leave
    ret  
    
df2: ;-2
    push ebp
    mov ebp, esp
    
    finit
    fld qword[q2]
    leave
    
    ret  
    
f3: ;-5/x
    push ebp
    mov ebp, esp
    
    finit
    fld qword[q5]
    fld qword[ebp+8]
    fdivp
    leave
    
    ret  
    
df3: ;5/x^2
    push ebp
    mov ebp, esp
    
    finit
    fld qword[q4]
    fld qword[ebp+8]
    fdivp
    fld qword[ebp+8]
    fdivp
    leave
    
    ret
    
test1: ;x+1
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp+8]
    fld1
    faddp
    leave
    
    ret

dtest1: ; 1
    push ebp
    mov ebp, esp
    
    finit
    fld1
    leave
    
    ret
    
test2: ; x^2-1
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
	fld qword[q7]
    faddp

    leave
    ret

dtest2: ;2x
    push ebp
    mov ebp, esp
    
    finit
    fld qword[q1]
    fld qword[ebp + 8]
    fmulp
    
    leave
    ret

test3: ; e^3x-3
    push ebp
    mov ebp, esp
    
    finit
	fld qword [ebp+8]
    fld qword[q6]
    fmulp
	fldl2e
	fmulp st1,st0      
	fld1
	fscale             
	fxch
	fld1
	fxch                
	fprem               
	f2xm1              
	faddp        
	fmulp 
	fld qword[q8]
	faddp

    leave    
    ret
    
dtest3: ; 3e^3x
    push ebp
    mov ebp, esp
    
    finit
	fld qword [ebp+8]
    fld qword[q6]
    fmulp
	fldl2e
	fmulp st1,st0      
	fld1
	fscale             
	fxch
	fld1
	fxch                
	fprem               
	f2xm1              
	faddp        
	fmulp 
    fld qword[q6]
    fmulp
    	
    leave
    ret