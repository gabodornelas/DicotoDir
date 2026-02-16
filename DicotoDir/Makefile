# Primero seleccionamos el compilador y las flags a usar
COMPILAR		= gcc
CFLAGS_COMMON	= -Wall

# Se ofrecerán dos posibilidades para que el usuario compile el programa
# Uno de estos será un programa de debugging, el otro será el release usual
# Entonces asignaremos distintas flags para cada opción.
CFLAGS_DEBUG    = $(CFLAGS_COMMON) -g3 -O0
CFLAGS_RELEASE  = $(CFLAGS_COMMON) -O2

# Aquí se colocan los archivos .c que van a compilarse para el programa 
SRC             = \
				main.c \
				estructura.c \
				procesos.c \
				validacionDatos.c \
				archivos.c \
				impresion.c

# De nuevo, separamos los archivos de debugging y los del release normal
OBJ_DEBUG       = $(SRC:.c=.debug.o)
OBJ_RELEASE     = $(SRC:.c=.release.o)

TARGET_DEBUG    = dicotodir_debug
TARGET_RELEASE  = dicotodir

.PHONY: all debug release clean

all: release

debug: $(TARGET_DEBUG)

release: $(TARGET_RELEASE)

# Esto sirve para borrar los .o intermedios. Comenta para debugging.
.INTERMEDIATE: $(OBJ_DEBUG)
.INTERMEDIATE: $(OBJ_RELEASE)

# Aquí se especifica como hacer make para el release y el debug
$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(COMPILAR) $(CFLAGS_DEBUG) -o $@ $^

$(TARGET_RELEASE): $(OBJ_RELEASE)
	$(COMPILAR) $(CFLAGS_RELEASE) -o $@ $^

# Esto es una wildcard y con ella se debería poder compilar cada archivo
# de forma individual, sea de debugging o de release
%.debug.o: %.c
	$(COMPILAR) $(CFLAGS_DEBUG) -c $< -o $@

%.release.o: %.c
	$(COMPILAR) $(CFLAGS_RELEASE) -c $< -o $@

# Esto es para cuando el usuario llama a make con el argumento "clean"
# En este caso, borramos cualquier archivo que hayamos generado antes
clean:
	rm -f *.debug.o *.release.o $(TARGET_DEBUG) $(TARGET_RELEASE)
