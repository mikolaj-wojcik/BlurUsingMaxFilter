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
;
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
brightArr QWORD 0
fWidth dWORD 0; 
fHeight QWORD 0
fNumOfRowsToToDo QWORD 0
startRow QWORD 0
fRay QWORD 0
retur QWORD 0

;void maxFilter(
;    std::byte* inputArr, std::byte* outputArr, int32_t* brightArr,
;    int32_t fWitdh, int32_t fHeight, int32_t fNumOfRowsToToDo,
;    int32_t startRow, int32_t fRay)

.code
maxFilter proc

;rcx- struct with integer values
;rdx- adress to inputArray
;r8- adress to output array
;r9- -adress to brightARray

mov rAX, [RCX]
mov inputArr, rDX 
add rcx, 8  ; przesunieæie ma byæ o 8  trzeba za³adowaæ do rejestru eax
mov eax, [RCX]
mov fWidth, eax
xor rax, rax

mov rcx, inputArr

Kreuz:
VPBROADCASTB XMM0, BYTE PTR[rcx]
VPBROADCASTB XMM1, BYTE PTR[rcx+1]
VPBROADCASTB XMM2, BYTE PTR[rcx+2]
inc rcx
inc rcx
inc rcx

jmp Kreuz
nop

HEIGHT: 

;WIDTH: ;Start of 2 main loops to itarate through each pixel in array

RAYHEIGHT: ;Loop to to find max brghness element in slected pixel neighbour

;if statement to check if selected index is in array range

RAYWIDTH: ;Loop to to find max brghness element in slected pixel neighbour

;if statement to check if selected index is in array range

;
;
;
;

MISSEDIFRAYWIDTHSTATEMENT: ; if rayWidth iterator is out of range


;JE RAYWIDTH;end of RAYWIDTH loop

;
MISSEDIFRAYHEIGHTSTATEMENT: ; if rayHeight iterator is out of range

;JE REYHEIGHT;end of RAYHEIGHT loop

;JE WIDTH;end of WIDTH loop

;JE HEIGHT;end of HEIGHT loop




ret
maxFilter endp
end
