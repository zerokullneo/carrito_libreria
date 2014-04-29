.PHONY: clean All

All:
	@echo "----------Building project:[ carrito_libreria - Debug ]----------"
	@$(MAKE) -f  "carrito_libreria.mk"
clean:
	@echo "----------Cleaning project:[ carrito_libreria - Debug ]----------"
	@$(MAKE) -f  "carrito_libreria.mk" clean
