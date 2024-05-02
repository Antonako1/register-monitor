.code
testFun proc
	mov eax, 100
	ret
testFun endp

getEaxR proc
	ret
getEaxR endp

getEbxR proc
	mov eax, ebx
	ret
getEbxR endp

getEcxR proc
	mov eax, ecx
	ret
getEcxR endp

getEdxR proc
	mov eax, edx
	ret
getEdxR endp

getEsiR proc
	mov eax, esi
	ret
getEsiR endp

getEdiR proc
	mov eax, edi
	ret
getEdiR endp

getEbpR proc
	mov eax, ebp
	ret
getEbpR endp

getEspR proc
	mov eax, esp
	ret
getEspR endp
end