int main() {
    char *filename = "example.txt";

    //reading file into buffer
	char *buffer = 0;
	file_to_buffer(&buffer, filename);
	printf("%s", buffer);
}