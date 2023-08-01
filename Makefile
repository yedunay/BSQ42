NAME = bsq

CC = gcc -c

CFLAGS = -Wall -Wextra -Werror

SRC = ./src/

DOTC = $(SRC)bsq.c $(SRC)ft_initialize_map.c $(SRC)ft_map_reading.c $(SRC)ft_square_drawing.c
DOTO = 	$(addprefix outputs/,$(notdir $(DOTC:.c=.o)))
INC = ./headers/

all : $(NAME) 

$(NAME): $(DOTO)
	gcc $(FLAG) -o $(NAME) $(DOTO) 

outputs/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)

clean : 
	/bin/rm -f *.o 

fclean : clean 
	/bin/rm -f $(NAME)

re : fclean all 

# NAME = bsq: Oluşturulacak programın adını "bsq" olarak belirler.
# CC = gcc -c: C dosyalarını derlemek için kullanılacak derleyiciyi belirtir. Burada "gcc -c" kullanılarak sadece nesne dosyaları oluşturulur (derlenir), yürütülebilir dosya oluşturulmaz.
# CFLAGS = -Wall -Wextra -Werror: Derleme sırasında derleyiciye iletilen bazı derleme bayraklarını belirtir. Bu bayraklar, derleme sürecinde uyarıları ve hataları etkinleştirecektir.
# SRC = ./src/: Kaynak dosyalarının bulunduğu dizini belirtir.
# DOTC = $(SRC)bsq.c $(SRC)ft_initialize_map.c $(SRC)ft_map_reading.c $(SRC)ft_square_drawing.c: Kaynak dosyalarının listesini oluşturur.
# DOTO = $(addprefix outputs/,$(notdir $(DOTC:.c=.o))): Nesne dosyalarının çıkış dizinini belirtir ve kaynak dosyalarının uzantılarını .c'den .o'ya değiştirir.
# INC = ./headers/: Başlık dosyalarının bulunduğu dizini belirtir.
# all : $(NAME): "all" adında bir hedef belirler, bu hedef "bsq" adlı yürütülebilir dosyanın oluşturulması için diğer hedefleri (nesne dosyaları oluşturma) çağıracaktır.
# $(NAME): $(DOTO): "bsq" adlı yürütülebilir dosyayı oluşturmak için kullanılan hedefi belirtir. Bu hedef, $(DOTO) değişkeninde tanımlanan nesne dosyalarını kullanarak "bsq" yürütülebilir dosyasını oluşturacaktır.
# gcc $(FLAG) -o $(NAME) $(DOTO): Yürütülebilir dosyanın oluşturulması için komutu belirtir. Nesne dosyaları $(DOTO) kullanılarak "bsq" adında bir yürütülebilir dosya oluşturulacaktır.
# outputs/%.o: src/%.c: Nesne dosyalarının oluşturulması için bir kural belirtir. Burada, her bir C dosyası için nesne dosyası oluşturulacak. Örneğin, "src/bsq.c" dosyasından "outputs/bsq.o" nesne dosyası oluşturulacaktır.
# $(CC) $(CFLAGS) -o $@ $< -I $(INC): Nesne dosyasını oluşturan komutu belirtir. "$@" sembolü, hedef dosyayı temsil eder (burada nesne dosyası), "$<" sembolü ise ilk bağımlılığı temsil eder (burada C dosyası). "-I $(INC)" bayrağı, derleyiciye başlık dosyalarının yerini belirtir.
# clean :: "clean" adında bir hedef belirler. Bu hedef, derleme sürecinden üretilen nesne dosyalarını silmeye yarar.
# /bin/rm -f *.o: Nesne dosyalarını silmek için komutu belirtir.
# fclean : clean: "fclean" adında bir hedef belirler. Bu hedef, "clean" hedefini çağıracaktır. Böylece "fclean" çalıştırıldığında önce nesne dosyaları silinecektir.
# /bin/rm -f $(NAME): Oluşturulan yürütülebilir dosyayı silmek için komutu belirtir.
# re : fclean all: "re" adında bir hedef belirler. Bu hedef, "fclean" hedefini çağıracak ve ardından "all" hedefini çağıracaktır. Böylece projeyi temizleyip yeniden derleyebilirsiniz.