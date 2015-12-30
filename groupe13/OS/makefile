OUTPUT=build
FS=tools/fs.img

MODE=normal

.PHONY: clean run kernel tools

$(OUTPUT).iso: kernel grub/grub.cfg $(OUTPUT)/boot/grub
	cp grub/grub.cfg $(OUTPUT)/boot/grub/
	cp kernel/kernel.elf $(OUTPUT)/boot/
	grub-mkrescue -o $@ $(OUTPUT)
	
kernel:
	@make -C kernel MODE=$(MODE)
	@make -C tools 

$(OUTPUT)/boot/grub:
	mkdir -p $@

run: $(OUTPUT).iso
	qemu-system-i386 -cdrom build.iso -hda tools/fs.img

clean:
	@make -C kernel clean
	@make -C tools clean
	rm -rf $(OUTPUT) $(OUTPUT).iso

