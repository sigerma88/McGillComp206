
phonebook: mini5main.o mini5phone.o
	gcc -o phonebook mini5main.o mini5phone.o

mini5main.o: mini5main.c mini5phone.h
	gcc -c mini5main.c

mini5phone.o: mini5phone.c mini5phone.h
	gcc -c mini5phone.c

test: phonebook
	if [ -f "./phonebook.csv" ]; then \
            rm ./phonebook.csv ; \
        fi
	./mini5tester.sh

run: phonebook
	chmod +x ./phonebook
	./phonebook

clean:
	if ls *.o >/dev/null 2>&1; then \
		rm *.o; \
	fi

	if [ -f "./phonebook" ]; then \
    		rm ./phonebook; \
	fi

backup:
	if [ ! -d "./backups" ]; then \
            mkdir ./backups ; \
	fi

	mkdir ./backups/mini5-$(USER)-$(shell date '+%Y-%m-%d-%H:%M:%S')
	cp *.c *.h ./backups/mini5-$(USER)-$(shell date '+%Y-%m-%d-%H:%M:%S')

