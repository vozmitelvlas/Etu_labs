.586
.MODEL FLAT, C
.CODE
first PROC C arr:dword, Xmin:dword, result_array:dword, length_:dword

mov edi, arr
mov ebx, result_array
mov ecx, length_
xor edx, edx
xor eax, eax

cycle:
	mov eax, [edi + 4 * edx] ; ��������

	test eax, 1
	jz s1
	sub eax, Xmin

	inc dword ptr [ebx + 4 * eax] ; ���������� �������� �����

	s1:
	inc edx ;��������� ��������
	loop CYCLE

finish:
	ret
	first endp
	end
