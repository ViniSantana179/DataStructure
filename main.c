#include <stdio.h>
#include <stdlib.h>

// Criando a estrutura dos Nos da nossa arvore
typedef struct Node{
    int id;
    struct Node * left;
    struct Node * right;
} Node;

// Criando a Arvore, onde tera um ponteiro apontando para a root (Primeiro Node) da Arvore
typedef struct ArvB{
    struct Node * root;
    int tam;
} ArvB;

void right_insert(Node * no, int val);
void left_insert(Node * no, int val);

void left_insert(Node * no, int val) {   
    if(!no->left)
    {
        Node * new_node = (Node *) malloc(sizeof(Node));
        new_node->id = val; 
        new_node->left = NULL; 
        new_node->right = NULL;
        no->left = new_node; 
    }
    else {
        if(val < no->left->id)
            left_insert(no->left, val);
        
        if(val > no->left->id)
            right_insert(no->left, val);
    }
}

void right_insert(Node * no, int val) {
    if(!no->right)
    {
        Node * new_node = (Node *) malloc(sizeof(Node));
        new_node->id = val; 
        new_node->left = NULL; 
        new_node->right = NULL;
        no->right = new_node; 
    }
    else
    {
        if(val < no->right->id)
            left_insert(no->right, val);

        if(val > no->right->id)
            right_insert(no->right, val);
    }    
}


void insert_node(ArvB * arv, int val){
    if(!arv->root)  // Arvore vazia, nao possui root
    
    {
        Node * new_node = (Node *) malloc(sizeof(Node));
        new_node->id = val; 
        new_node->left = NULL;
        new_node->right = NULL;
        arv->root = new_node;
    }
    else
    {
        if(val < arv->root->id)
            left_insert(arv->root, val);
        
        if(val > arv->root->id)
            right_insert(arv->root, val);
    }
}

// Maneira mais elegante e simples para realizar a insercao de nos.
Node * insert_new_node(Node * root, int val) {
    if(!root)
    {
        Node * new_node = (Node *) malloc(sizeof(Node));
        new_node->id = val; 
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    else
    {
        if (val < root->id)
            root->left = insert_new_node(root->left, val);
        if (val > root->id)
            root->right = insert_new_node(root->right, val);
        return root;
    }
}

int lenght(Node * root) {
    if(!root) return 0;
    return 1 +lenght(root->left) + lenght(root->right);
}

int buscaNumero(Node * root, int chave) {
    if(!root) {
        return 0;
    }
    else {
        if(root->id == chave) return 1;
        else {
            if(root->id > chave) return buscaNumero(root->left, chave);
            if(root->id < chave) return buscaNumero(root->right, chave);
        }
    }
}

Node * remove_node(Node * root, int id) {
    if (!root) {
        printf("Valor nao encontrado.\n");
        return NULL;
    }
    else {
        if(root->id == id) {
            // remove nos folhas - nos sem filhos
            if(!root->right && !root->left) {
                free(root); 
                return NULL;
            }
            else {
                // remove nos com ao menos um filho
                if(root->right || root->left) {
                    Node * tmp;
                    if(root->right) tmp = root->right;
                    if(root->left) tmp = root->left;
                    free(root);
                    return tmp;
                }
                else {
                    Node * aux = root->left;
                    while(aux->right)  aux = aux->right;
                    root->id = aux->id;
                    aux->id = id;
                    root->left = remove_node(root->left, id);
                    return root;

                }

            }
        }
        else {
            if(id > root->id) root->right = remove_node(root->right, id);
            if(id < root->id) root->left  = remove_node(root->left, id);
            return root;
        }
    }

}


// Imprimir os nodes da minha arvore
void print_node(Node * root) {
    if(!root) return;
    print_node(root->left);
    printf(" %d", root->id);
    print_node(root->right);

}



int main()  {

    int op, val;
    ArvB arv;
    arv.root = NULL;

    // Melhorando minha insercao
    Node * root = NULL;

    do
    {
        printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Buscar\n4 - remover\n");
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            printf("Saindo ...");
            break;
        case 1:
            printf("Digite um Valor: ");
            scanf("%d", &val);
            root = insert_new_node(root, val);
            //insert_node(&arv, val);
            break;
        case 2:
            printf("\nImpressao da arvore binaria: \n");
            print_node(root);
            printf("\n");
            printf("Tamanho:  %d", lenght(root)); 
            break;
        case 3:
            printf("\nQual valor deseja buscar? \n");
            scanf("%d", &val);
            printf("Resultado da busca: %d\n", buscaNumero(root, val));
            break;
        case 4:
            printf("\nQual valor deseja remover? \n");
            scanf("%d", &val);
            root = remove_node(root, val);
            break;
        default:
            printf("\nOpcao invalida.");
            break;
        }
    } while (op != 0);
    
}