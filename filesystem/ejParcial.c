struct Ext2FSDirEntry {
unsigned int inode;
unsigned short record_length;
unsigned char name_length;
unsigned char file_type;
char name[];
};
struct Ext2FSInode {
unsigned short mode; // info sobre el tipo de archivo y los permisos
unsigned short uid; // id de usuario
unsigned int size; // tama\~no en bytes
unsigned int atime;
unsigned int ctime;
unsigned int mtime; // fecha ultima modificacion
unsigned int dtime;
unsigned short gid; // id de grupo
unsigned short links_count; // cantidad de enlaces al archivo
unsigned int blocks;
unsigned int flags;
unsigned int os_dependant_1;
unsigned int block[15];
unsigned int generation;
unsigned int file_acl;
unsigned int directory_acl;
unsigned int faddr;
unsigned int os_dependant_2[3];
};
Se cuenta tambi´en con la constante BLOCK_SIZE y con las siguientes funciones:
char * tipo_y_permisos(unsigned short mode)
// dado el campo mode de un inodo, devuelve una cadena denotando el tipo y
// permisos tal como lo hace ls
struct Ext2FSInode * Ext2FS::inode_for_path(const char * path)
// dado un path, devuelve su inodo
void Ext2FS::read_block(unsigned int block_address, unsigned char * buffer)
// dada una direccion de bloque y un buffer, carga el bloque indicado
// en el buffer
unsigned int Ext2FS::get_block_address(struct Ext2FSInode * inode, unsigned int block_number)
// dados un inodo y un numero de bloque, recorre el inodo buscando la
// direccion del bloque de datos indicado
structExt2FSInode * Ext2FS::load_inode(unsigned int inode_number)
// dado un numero de inodo, busca el inodo en el grupo y lo devuelve
char *strncpy(char *dest, const char *src, size_t n)
// funci´on de C que copia en dest hasta n caracteres del string src
// si la longitud de src es menor a n, se completa el resto de dest con null
void imprimirls(char * dentry) {
    char * format = "%d %s %d %s %s %d %s %s";
    char * nombre[dentry.name_length];
    Ext2FSInode* inodo = load_inode(dentry.inode);
    printf(format, dentry.inode, tipo_y_permisos(inodo.mode), 
    inodo.links_count, dame_user(inodo.uid), dame_grupo(inodo.gid),
    inodo.size, dame_fecha(inodo.mtime), strncpy(nombre,dentry.name, dentry.name_length ));
}

int lsParcial(char * dir){
    Ext2FSInode* inodoDir = inode_for_path(dir);
    unsigned char* buffer_bloque = (unsigned char*) malloc(BLOCK_SIZE * 2);
    unsigned char* buffer_siguiente = buffer_bloque + BLOCK_SIZE;
    int dir_bloque_1, dir_bloque_2; int num_bloque = 0; int recorrido = 0; int offset_dentry = 0;

    while(recorrido < inodoDir.size ){
        dir_bloque_1 = get_block_address(inodoDir, num_bloque);
        dir_bloque_2 = get_block_address(inodoDir, num_bloque+1);
        read_block(dir_bloque_1, buffer_bloque);
        read_block(dir_bloque_2, buffer_siguiente);
        Ext2FSDirEntry* dentry = (Ext2FSDirEntry*)buffer_bloque + offset_dentry;
        imprimirls(dentry); //falta completar
        offset_dentry += dentry.record_length;
        recorrido += dentry.record_length;
        if(offset_dentry> BLOCK_SIZE){
            offset_dentry - BLOCK_SIZE;
            num_bloque++;
        }
    }
}

//la longitud de direntry es variable en ext2, mientras q en fat es fijo
/*
lsparcial(path)
-cargar inodo de path
-recorrer bloques de datos, asi voy mirando dentries
*/