PROJECT_NAME = blink
SOURCES = main.c

all: $(PROJECT_NAME).hex

$(PROJECT_NAME).hex: $(SOURCES)
    sdcc -mmcs51 --model-small --out-fmt-ihx $(SOURCES)
    packihx $(PROJECT_NAME).ihx > $(PROJECT_NAME).hex

clean:
    rm -f $(PROJECT_NAME).hex $(PROJECT_NAME).ihx $(PROJECT_NAME).lk $(PROJECT_NAME).lst $(PROJECT_NAME).map
