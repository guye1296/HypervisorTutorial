bits 64

section: .text

global vmxonInternal
global _vmxonInternal@4

; This function is only implemented because 
; for some reason `__vmx_on()` is not found
; of my machine
; note that the decorated name of void vmxonInternal(size_t)
; is translated to  _vmxonInternal@4
; see: 
vmxonInternal:
_vmxonInternal@4:
; argument should be passed via `rcx`
; rcx is expected to contain a pointer to variable
; storing the physical address of the vmxon region
	vmxon [rcx]
	ret

