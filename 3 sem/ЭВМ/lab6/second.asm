.586
.MODEL FLAT, C
.CODE
second PROC C arr:dword, result:dword, L_array:dword, Xmin:dword, Xmax:dword

;arr - ������ ���������� ���� ���� �� ��������� �������
;result - �������� �������
;L_array - ������ ����� ������
;Xmin - ��������� �������� �������
;Xmax - �������� �������� �������

mov eax, Xmin ; �������� �� �������
xor ebx, ebx
xor ecx, ecx
mov edi, result
mov edx, L_array
mov esi, arr

cycle:
	cmp eax, [edx + 4] ;���� ����� ����� �� ������� ������� �������
	jge adding ;������� �� ����� �������

mov ebx, [esi + ecx * 4] ;���������� ���� 
add[edi], ebx ;���������� � �������
inc ecx ;������� ��� ������� ���������� ����
inc eax ;c�������� �����

cmp eax, Xmax
jle cycle
jmp finish

adding:
	add edi, 4 ;��������� ������ ��������� �������
	add edx, 4 ;��������� �������
	jmp cycle

finish:
	ret
	second endp
	end
