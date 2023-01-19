;----------------------------------------------------------------
;	Library which transforms input array of bgr pixels to output array by using maximum fiter method
;	
;
;
;
;
;
;
;versions:
; 0.1- library  created(11.01.2023)
; 0.2- added parameters load (12.01.2023)
; 0.3- added loops (18.01.2023)
; 0.4- made basic algorith modifyng picture (19.01.2023)
;
;
;
;----------------------------------------------------------------

.data
itHeight DWORD 0
itWidth DWORD 0
itRayHeight DWORD 0
itRayWidth DWORD 0

inputArr qWORD 0
outputArr QWORD 0
brightArr qWORD 0
fWidth dWORD 0; 
fHeight dWORD 0
fNumOfRowsToDo dWORD 0
endRow dword 0
startRow dWORD 0
fRay dWORD 0
retur QWORD 0


.code
maxFilter proc

;rcx- struct with integer values
;rdx- adress to inputArray
;r8- adress to output array
;r9- -adress to brightARray

mov rAX, [RCX]
add rcx, 4  ; przesunie�ie ma by� o 8  trzeba za�adowa� do rejestru eax
mov fWidth, eax
mov rax, [RCX]
mov fHeight, eax
add rcx, 4  ; przesunie�ie ma by� o 8  trzeba za�adowa� do rejestru eax
mov rax, [RCX]
mov fNumOfRowsToDo, eax
add rcx, 4  ; przesunie�ie ma by� o 8  trzeba za�adowa� do rejestru eax
mov rax, [RCX]
;sub eax, 1; ray includes center pixel, ex. if center pixel =17, ray=3 you have to to 
			;check pixels 15, 16 ,18, 19. Two from each site
mov fRay, eax
add rcx, 4  ; przesunie�ie ma by� o 8  trzeba za�adowa� do rejestru eax
mov rax, [RCX]
mov startRow, eax
mov inputArr, RDX 
mov outputArr, r8
mov brightArr, r9


xor rax, rax


;mov r1, fWidth
;mov r2, fHeight

;rcx- iterator through main array
;rdx- end pixel


;;;;;;;;;;;;;;;;;;;;
;Initializng start and end index of main loop

xor rcx, rcx
xor rdx, rdx ; clear index registers
mov ecx, startRow; 
mov ebx,  fWidth
imul ecx, ebx ; calculate starting index of pixel array
;imul ecx, 3 ;each pixel contains 3 elements in array
mov edx, startRow; load starting index to end index register
add edx, fNumOfRowsToDo; get last row number required to edit
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

xor rax, rax
mov eax, fWidth; load width offset to calculate index
imul rax, rcx; multply by already processed rows of picture
add rax, rdx; add number of columns already processed
mov r12, rax; save index of current modyfing index to regiuter
imul rax,2
add rax, brightArr
mov bx, word ptr[rax];load bright value of current modified pixel to register
mov r13, rbx;



xor rax, rax
mov eax, fHeight

;rbx is used to store fRay value



;if statement to check if selected index is in array range
cmp r8, 0; check if current ray iterator is in pixelArray range
JL RayHeightLessThanZero ;if iterarto is lesst than zero load zero to start iterating
;;;;;Start of rays  outer loop
RAYHEIGHT: ;Loop to to find max brghness element in slected pixel neighbour


xor rax, rax
mov eax, fHeight	;load number of picture rows
cmp r8, rax; check if ray iterator is still in pixelArray range
JGE RayHeightEndLoop ; if not, exit all ray loops

RayHeightAfterEvZero:
;initializng itarator through width of 
;kernel to select maxBrightness element

xor rbx, rbx
mov ebx , fRay
mov r9, rdx
sub r9, rbx



cmp r9, 0; ; check if current ray iterator is in pixelArray range
JL RayWidthLessThanZero
;;;;;Start of rays inner loop
RAYWIDTH: ;Loop to to find max brghness element in slected pixel neighbour

;if statement to check if selected index is in array range


xor rax, rax	;load array width
mov eax, fWidth	;
cmp r9, rax		;if iterator is already out of array scope jump out of rayWidth loop
JGE RayWidthEndLoop
RayWidthAfterEvZero:

;Comparing bright Value of neighbour pixel to select max value
;If theres max vaklue, save index and value
;calculate current index
xor rax, rax
mov eax, fWidth; load offset caused by row idth
imul rax, r8;load row
add rax, r9;load column
mov r14, rax; temproary save index
imul rax, 2; multiply by width of DWORD
add rax, brightArr

mov bx, word ptr[rax]; load bright value
cmp rbx, r13; check if new value is higher than current highest
JG saveNewValue;if yes save nev value and index
retFromSave:


inc r9
cmp r9, r11
JLE RAYWIDTH;end of RAYWIDTH loop
RayWidthEndLoop:



inc r8
cmp r8, r10
JLE RaYHEIGHT;end of RAYHEIGHT loop

RayHeightEndLoop:

;
;Place to put pixel moving
;

mov rax, r12
imul rax, 3
add rax, inputArr

VPBROADCASTB  xmm0, byte ptr [rax]
inc rax
VPBROADCASTB  xmm1, byte ptr [rax]
inc rax
VPBROADCASTB  xmm2, byte ptr [rax]

xor rax, rax
mov eax, fWidth
imul rax, rcx
add rax, rdx
imul rax, 3
add rax, outputArr

movd r12, xmm0
movd r13, xmm1
movd r14, xmm2

mov byte ptr[rax], r12b
mov byte ptr[rax+1], r13b
mov byte ptr[rax+2], r14b


xor rbx, rbx
mov ebx, fWidth
inc rdx
cmp rdx, rbx
JL PictureWidth
;########end of WIDTH loop########

xor rbx, rbx
mov ebx, endRow
inc rcx
cmp rcx, rbx; 
JL PictureHeight
;########end of HEIGHT loop#######




ret

RayHeightLessThanZero:
mov r8, 0
JMP RayHeightAfterEvZero

RayWidthLessThanZero:
mov r9, 0
JMP RayWidthAfterEvZero

SaveNewValue:
mov r13, rbx; save new value
mov r12, r14;save index
JMP retFromSave
maxFilter endp
end
