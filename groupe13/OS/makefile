OUTPUT=build
FS=tools/fs.img

MODE=normal

.PHONY: clean run kernel doc

$(OUTPUT).iso: kernel tools grub/grub.cfg $(OUTPUT)/boot/grub
	cp grub/grub.cfg $(OUTPUT)/boot/grub/
	cp kernel/kernel.elf $(OUTPUT)/boot/
	grub-mkrescue -o $@ $(OUTPUT)

kernel:
	@make -C kernel MODE=$(MODE)
	
tools:
	@make -C tools

$(OUTPUT)/boot/grub:
	mkdir -p $@

run: $(OUTPUT).iso
	qemu-system-i386 -hda $(FS)

clean:
	@make -C kernel clean
	rm -rf $(OUTPUT) $(OUTPUT).iso

