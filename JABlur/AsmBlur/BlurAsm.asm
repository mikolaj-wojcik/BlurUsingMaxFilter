;----------------------------------------------------------------
;	Library which transforms input array of bgr pixels to output array by using maximum fiter method
;	Parameters passed to function:
;	-Struct containing rquired data to process image
;	-pointer to byte array with input image
;	-pointer to byte array where output image will be stored
;	-pointer to uint16 array with data of each pixel brightness
;
;
;versions:
; 0.1- library  created(11.01.2023)
; 0.2- added parameters load (12.01.2023)
; 0.3- added loops (18.01.2023)
; 0.4- made algorithm modifying picture (19.01.2023)
; 0.5- fixed bug that top rows hasnt been blurred correctly(20.01.2023)
; 1.0- added comments and removed dead code (24.01.223)
; 1.1- partially removed threding problem(01.02.2023)
; 1.2- removed multthreading bug(01.02.2023)
;----------------------------------------------------------------

.data

inputArr qWORD 0; variable which stores adress of input array
outputArr QWORD 0;  variable which stores adress of output array
brightArr qWORD 0; variable which stores adress of pixel brightness array
fWidth dWORD 0; width of image
fHeight dWORD 0; heigh of image
fNumOfRowsToDo dWORD 0; 
endRow dword 0
startRow dWORD 0; 
fRay dWORD 0



.code
maxFilter proc

;rcx- struct with integer values
;rdx- adress to inputArray
;r8- adress to output array
;r9- -adress to brightARray

mov rAX, [RCX]
add rcx, 4  ; offset iterator to get access to next vaklue of struct
mov fWidth, eax
mov rax, [RCX]
sub eax, 1; 
mov fHeight, eax
add rcx, 4  ; offset iterator to get access to next vaklue of struct
mov rax, [RCX]

mov fNumOfRowsToDo, eax
add rcx, 4  ; offset iterator to get access to next vaklue of struct
mov rax, [RCX]
mov fRay, eax
add rcx, 4  ;; offset iterator to get access to next vaklue of struct
mov rax, [RCX]
mov startRow, eax
mov inputArr, RDX 
mov outputArr, r8
mov brightArr, r9





;rcx- iterator through main array
;rdx- end pixel


;;;;;;;;;;;;;;;;;;;;
;Initializng start and end index of main loop

xor rax, rax
xor rcx, rcx
xor rdx, rdx ; clear index registers
mov ecx, startRow; 



mov edx, startRow; load starting index to end index register
add edx, fNumOfRowsToDo; get last row number required to edit
sub edx,1
mov eax, fHeight
cmp edx, eax
JG endRowOut ; compare if calculated endRow is in picture range

endRowOutRet:

mov endRow, edx; save last row
;;;;;;;;;;;;;;;;;;;;




;;;;;;;;Start of loop through pixel array
;rcx- iterator height register
PictureHeight: 



xor rdx, rdx ; clear width iterator register

;;;;;;;;Start of inner loop
PictureWidth:

;r8- ray height
;r9 ray width
;r10 -max ray height
;r11- max ray width
;r12- index of maxBright pixel


;initializng itarator through width of 
;kernel to select maxBrightness element

xor rbx, rbx
mov ebx , fRay
mov r8, rcx
mov r10, rcx
sub r8, rbx
add r10, rbx
mov r11, rdx
add r11, rbx

;initiazling labels
xor rax, rax
mov r12,rax
mov r13, rax





;rbx is used to store fRay value

cmp r8, 0; check if current ray iterator is in pixelArray range

JL RayHeightLessThanZero ;if iterator is less than zero load zero to start iterating alredy in picture


;;;;;Start of rays  outer loop
RAYHEIGHT: ;Loop to to find max brghness element in slected pixel neighbour

xor rax, rax
mov eax, fHeight	;load number of picture rows
cmp r8, rax; check if ray iterator is still in pixelArray range

JGE RayHeightEndLoop
RayHeightAfterEvZero:

;initializng itarator through width of 
;kernel to select maxBrightness element
xor rbx, rbx
mov ebx , fRay
mov r9, rdx
sub r9, rbx; Subtract value of ray from current pixel width index to get better



cmp r9, 0; ; check if current ray iterator is in pixelArray range
JL RayWidthLessThanZero

;;;;;Start of rays inner loop
RAYWIDTH: ;Loop to to find max brghness element in slected pixel neighbour

;if statement to check if selected index is in array range


xor rax, rax	;
mov eax, fWidth	;load array width
cmp r9, rax		;if iterator is already out of array scope jump out of rayWidth loop
JGE RayWidthEndLoop

RayWidthAfterEvZero:

;Comparing bright Value of neighbour pixel to select max value
;If theres max value, save index and value
;calculate current index
xor rax, rax
mov eax, fWidth; load offset caused by row width
imul rax, r8;load row
add rax, r9;load column
mov r14, rax; temproary save index
imul rax, 2; multiply by width of DWORD
add rax, brightArr

xor rbx, rbx
mov bx, word ptr[rax]; load bright value
cmp bx, 0; check if max brightness value has been found
JL retFromSave; if loaded number is negative dont compare
cmp rbx, r13; check if new value is higher than current highest
JG saveNewValue;if yes save new value and index
retFromSave:


inc r9 ;increment current width iterator through width
cmp r9, r11; check if ray itertor is in kernel width range
JLE RAYWIDTH;if not, end of RAYWIDTH loop
;######End Of Ray Width######
RayWidthEndLoop:



inc r8 ;increment current width iterator through height
cmp r8, r10; check if ray height iterator is in kernel height range
JLE RaYHEIGHT;if not, end of RAYHEIGHT loop

;######End Of Ray Height######
RayHeightEndLoop:
;procedure to copy to modyfing pixel data of brightest pixel in arrea

mov rax, r12 ;load brightest pixel index
imul rax, 3; calculate offset
add rax, inputArr; add address of array

VZEROALL ;clearing colours register
;copy all colours from pixel 
;to temproary register
VPBROADCASTB  xmm0, byte ptr [rax]
inc rax
VPBROADCASTB  xmm1, byte ptr [rax]
inc rax
VPBROADCASTB  xmm2, byte ptr [rax]

;calculate index of curront modified pixel
;to load pixel data from temp registers to them
xor rax, rax
mov eax, fWidth
imul rax, rcx
add rax, rdx
imul rax, 3
add rax, outputArr


;save brightest pixel data into outputArray
movd r12d,xmm0
movd r13d, xmm1
movd r14d, xmm2
mov byte ptr[rax], r12b
inc rax
mov byte ptr[rax], r13b
inc rax
mov byte ptr[rax], r14b


skipCopy:; if modified pixel and source pixel is the same skip operation

xor rbx, rbx
mov ebx, fWidth; load width to comapre 
inc rdx
cmp rdx, rbx ;copmpare if width iterator is still in picture tange,
JL PictureWidth; if not start modyfing new row
;########end of WIDTH loop########

xor rbx, rbx
mov ebx, endRow
inc rcx
cmp rcx, rbx; compare if heght itertor is in designed range
JLE PictureHeight; if not end procedure and exit function
;########end of HEIGHT loop#######


;mov Rax, outputArr

ret

;Procedures to move zero into iterator if ray height iterator is out of picture range
RayHeightLessThanZero:
mov r8, 0

JMP RayHeightAfterEvZero

;Procedures to move zero into iterator if ray width iterator is out of picture range
RayWidthLessThanZero:
mov r9, 0
JMP RayWidthAfterEvZero

;procedure called when new vale is hisgher than current highest
SaveNewValue:

mov r13, rbx; save new value
mov r12, r14;save index
JMP retFromSave

;if calculated row is outside of picture range
;load intead maximum picture row
endRowOut:
mov edx,eax
JMP endRowOutRet
maxFilter endp
end
