#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

size_t my_strlen(const char* s)
{
	size_t size = 0;
	size_t i = 0;
	while(s[i] != '\0')
	{
		size += 1;
		i += 1;
	}
	return size;
}


char* my_strcat(char* dest, const char* src)
{
	size_t i = my_strlen(dest);
	
	size_t j = 0;
	while(src[j] != '\0')
	{
		dest[i] = src[j];
		j += 1;
		i += 1;
	}
	dest[i++] = '\0';
	
	return dest;
}


char* my_strncat(char* dest, const char* src, size_t n)
{
	size_t i = my_strlen(dest);
	
	size_t j = 0;
	while(src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		j += 1;
		i += 1;
	}
	dest[i++] = '\0';
	
	return dest;
}


char* my_strcpy(char* dest, const char* src)
{
	size_t i = 0;
	while(src[i] != '\0')
	{
		dest[i] = src[i];
		i += 1;
	}
	dest[i++] = '\0';
	
	return dest;
}


char* my_strncpy(char* dest, const char* src, size_t n)
{
	size_t i = 0;
	while(src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i += 1;
	}
	
	if(n >= my_strlen(src))
		dest[i++] = '\0';
	
	return dest;
}


char* my_strdup(const char* s)
{
	size_t len_s = my_strlen(s);
	char* dup = malloc((len_s + 1) * sizeof(char));
	size_t i = 0;
	for(; i < len_s + 1; ++i)
	{
		dup[i] = s[i];
	}
	return dup;
}


char* my_strndup(const char* s, size_t n)
{
	size_t len_s = my_strlen(s);
	char* dup = malloc(n * sizeof(char));
	size_t i = 0;
	for(; i < n; ++i)
	{
		dup[i] = s[i];
	}
	if(n < len_s)
		dup[i++] = '\0';
	return dup;
}


int my_strcmp(const char* s1, const char* s2)
{
	for(size_t i = 0; i < my_strlen(s1); ++i)
	{
		if(s1[i] > s2[i])
			return 1;
		else if(s1[i] < s2[i])
			return -1;
	}
	if(my_strlen(s1) == my_strlen(s2))
	{
		return 0;
	}
	else return -1;
}


int my_strncmp(const char* s1, const char* s2, size_t n)
{
	for(size_t i = 0; i < n; ++i)
	{
		if(s1[i] > s2[i])
			return 1;
		else if(s1[i] < s2[i])
			return -1;
	}
	return 0;
}


char* my_strchr(const char* s, int c)
{
	size_t i = 0;
	char* ptr = NULL;
	while(s[i + 1] != '\0')
	{
		if(s[i] == c)
		{
			ptr = &s[i];
			return ptr;
		}
		else i += 1;
	}
	return NULL;
}


char* my_strrchr(const char* s, int c)
{
	size_t i = my_strlen(s) + 1;
	char* ptr = NULL;
	while(i != 0)
	{
		if(s[i] == c)
		{
			ptr = &s[i];
			return ptr;
		}
		else i -= 1;
	}
	return NULL;
}


char* my_strstr(const char* haystack, const char* needle)
{
	size_t len_n = my_strlen(needle);
	size_t i = 0;
	while(haystack[i] != '\0')
	{
		if(haystack[i] == needle[0])
		{
			size_t j = 1;
			while(needle[j] != '\0')
			{
				if(haystack[i + j] != needle[j])
				{
					break;
				}
				j += 1;
			}
			if(j == len_n)
			{
				return &haystack[i];
			}
		}
		i += 1;
	}
	return NULL;
}


char* my_strtok(char* str, const char* delim)
{
	static char* ptr = NULL;
	size_t i = 0;
	bool found_delim = false;
	char* token = NULL;
	
	if(ptr == NULL) //première invocation
	{
		token = &str[0];
		ptr = token;
	}
	else
	{
		if(str != NULL)
		{
			fprintf(stderr, "str must be NULL after the first invocation of strtok\n");
			exit(EXIT_FAILURE);
		}
		else if(ptr[0] == '\0') //cas où il n'y avait qu'un seul groupe de délimiteur au début de la string
		{
			return NULL;
		}
		token = &ptr[0];
	}
	
	while(ptr[i] != '\0')
	{
		for(size_t j = 0; j < my_strlen(delim); ++j)
		{
			if(ptr[i] == delim[j])
			{
				found_delim = true;
			}
		}
		
		if(found_delim)
		{
			ptr[i] = '\0';
			if(my_strlen(token) == 0)
			{
				//aucun token encore trouvé, il ne faut pas retourner maintenant !
				i += 1;
				token = &ptr[i];
				found_delim = false;
			}
			else 
			{
				ptr = &ptr[i + 1];
				return token;
			}
		}
		else i += 1;
	}
	//cas où aucun délimiteur n'a été trouvé
	if(my_strlen(token) == 0)
	{
		return NULL;
	}
	else
	{
		ptr = &ptr[i];
		return token;
	}
}


char* my_strpbrk(const char* s, const char* accept)
{
	size_t len_s = my_strlen(s);
	size_t len_a = my_strlen(accept);
	for(size_t i = 0; i < len_s; ++i)
	{
		for(size_t j = 0; j < len_a; ++j)
		{
			if(s[i] == accept[j])
			{
				return &s[i];
			}
		}
	}
	return NULL;
}


size_t my_strspn(const char* s, const char* accept)
{
	//partir du début de s, chercher dans accept (peu importe si une lettre est présente plusieurs fois dans accept) si s[i] appartient à accept. 
	//Si oui, incrémentation de length, si non return la length
	
	size_t len_s = my_strlen(s);
	size_t len_a = my_strlen(accept);
	size_t length = 0;
	bool letter_found = false;
	
	for(size_t i = 0; i < len_s; ++i)
	{
		for(size_t j = 0; j < len_a; ++j)
		{
			if(s[i] == accept[j])
			{
				length += 1;
				letter_found = true;
				break;
			}
		}
		if(!letter_found)
		{
			break;
		}
		else letter_found = false;
	}
	return length;
}


size_t my_strcspn(const char* s, const char* accept)
{
	size_t len_s = my_strlen(s);
	size_t len_a = my_strlen(accept);
	size_t length = 0;
	
	for(size_t i = 0; i < len_s; ++i)
	{
		for(size_t j = 0; j < len_a; ++j)
		{
			if(s[i] == accept[j])
			{
				return length;
			}
		}
		length += 1;
	}
	return length;
}


void* my_memset(void* s, int c, size_t n)
{
	for(size_t i = 0; i < n; ++i)
	{
		((unsigned char*)s)[i] = c;
	}
	return s;
}


void* my_memmove(void* dest, const void* src, size_t n)
{
	unsigned char temp[n];
	for(size_t i = 0; i < n; ++i)
	{
		temp[i] = ((unsigned char*)src)[i];
		((unsigned char*)dest)[i] = temp[i];
	}
	return dest;
}


void* my_memcpy(void* dest, const void* src, size_t n)
{
	for(size_t i = 0; i < n; ++i)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
	}
	return dest;
}


void* my_memccpy(void* dest, const void* src, int c, size_t n)
{
	for(size_t i = 0; i < n; ++i)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		if(((unsigned char*)src)[i] == c)
		{
			break;
		}
	}
	return dest;
}


int my_memcmp(const void* s1, const void* s2, size_t n)
{
	if(n == 0)
	{
		return 0;
	}

	for(size_t i = 0; i < n; ++i)
	{
		if(((unsigned char*)s1)[i] != ((unsigned char*)s2)[i])
		{
			return ((unsigned char*)s1)[i] - ((unsigned char*)s2)[i];
		}
	}
	return 0;
}


void* my_memchr(const void* s, int c, size_t n)
{
	for(size_t i = 0; i < n; ++i)
	{
		if(((unsigned char*)s)[i] == c)
		{
			return &s[i];
		}
	}
	return NULL;	
}


void* my_memrchr(const void* s, int c, size_t n)
{
	for(size_t i = n - 1; i != 0; --i)
	{
		if(((unsigned char*)s)[i] == c)
		{
			return &s[i];
		}
	}
	return NULL;	
}


int main(void)
{
	char* s = my_strndup("aobocodoeofog", 14);
	
	char* ptr = my_strpbrk(s, "g");
	printf("%c\n", *ptr);
	
	size_t len = strcspn(s, "f");
	printf("Len : %ld\n", len);
	
	char tab1[12] = {"mbcdefghiej"};
	char tab2[12] = {"abcdefghijk"};
	printf("%d\n", memcmp(tab1, tab2, 12));
	
	char* pointer = memchr(tab1, 'e', 12);
	printf("Adresse : %p, valeur : %c\n", pointer, *pointer);
	pointer = my_memchr(tab1, 'e', 12);
	printf("Adresse : %p, valeur : %c\n", pointer, *pointer);
	
	char* token = my_strtok(s, "o");
	while(token != NULL)
	{
		printf("%s\n", token);
		token = my_strtok(NULL, "o");
	}
	
	free(s);
	
	return 0;
}
