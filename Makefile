NAME = bsq

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = bsq.c

all : $(NAME) #projenin tamamini derlemek ve ardindan calistirabilir bir dosya olusturmak icin kullanilir. Cok daha duzenli bir yapi ve tekrar kullanılabilirlik saglar.

 #calistirilabilir dosya olusturmak icin kullanilir.
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean : #Bu target tanımında anlatılan , derleme sırasında olusan gecici .o uzantili dosyalari temizlemektir.
	/bin/rm -f *.o 

fclean : clean #Bu hedef clean hedefini cagirarak onceden olusan her turlu nesne doyalarını siler , sonra projenin calıstırabilir dosyasini siler , yani bu hedefle birlikte hem gecici doyalri hem de projenin calistirailabir doyasını temizlemis bir bakima resetlemis olursunuz.
	/bin/rm -f $(NAME)

re : fclean all #bu hedef projeyi sifirdan derlemek icin kullanilir , make fclean ve make all komutlarinin birlesimidir.