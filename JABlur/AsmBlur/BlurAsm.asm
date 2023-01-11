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
;
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


.code
maxFilter proc

HEIGHT: 
WIDTH: ;Start of 2 main loops to itarate through each pixel in array

RAYHEIGHT: ;Loop to to find max brghness element in slected pixel neighbour

;if statement to check if selected index is in array range

RAYWIDTH: ;Loop to to find max brghness element in slected pixel neighbour

;if statement to check if selected index is in array range

;
;
;
;

MISSEDIFRAYWIDTHSTATEMENT: ; if rayWidth iterator is out of range


;end of RAYWIDTH loop

;
MISSEDIFRAYHEIGHTSTATEMENT: ; if rayHeight iterator is out of range

;end of RAYHEIGHT loop

;end of WIDTH loop

;end of HEIGHT loop




ret
maxFilter endp
end