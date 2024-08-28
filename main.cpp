#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

class Produto{

    private:
    string nome;
    float valor;
    int quantidade;

    public:
    Produto(string nome, float valor, int quantidade)
    : nome(nome), valor(valor), quantidade(quantidade){}

    string getNome() const{
        return nome;
    }

    void setNome(string nome){
        this->nome = nome;
    }

    float getValor() const{
        return valor;
    }

    void setValor(float valor){
        this->valor = valor;
    }

    int getQuantidade() const{
        return quantidade;
    }

    void setQuantidade(int quantidade){
        this->quantidade = quantidade;
    }
    
};


class Estoque{

    public:

    list<Produto> listProdutos;

    void adicionaProduto(Produto produto){
        listProdutos.push_back(produto);
    }

    void removerProdutos(string nome, int quantidade) {
        for (auto it = listProdutos.begin(); it != listProdutos.end(); it++) {
            if (it->getNome() == nome) {
                if (it->getQuantidade() >= quantidade) {
                    it->setQuantidade(it->getQuantidade() - quantidade);
                    if (it->getQuantidade() <= 0) {
                        it = listProdutos.erase(it);  // Remover produto e obter novo iterador
                    }
                } else {
                    cout << "Quantidade insuficiente em estoque!" << endl;
                }
                break;
            }
        }
    }

    Produto* buscarProduto(const string& nome) {
        for (auto& produto : listProdutos) {
            if (produto.getNome() == nome) {
                return &produto;
            }
        }
        return nullptr;
    }

    void exibirEstoque() const {
    cout << "Estoque de Produtos:\n";
        for (const auto& produto : listProdutos) {
            cout << "Nome: " << produto.getNome()
                << ", Quantidade: " << produto.getQuantidade()
                << ", Valor: R$ " << fixed << setprecision(2) << produto.getValor() << endl;
        }
    }
};



class CarrinhoCompras{
    private:

    Estoque& estoque;

    public:

    list<Produto> compras;

    CarrinhoCompras(Estoque& estoque) : estoque(estoque) {}

    void adicionaCompra(const string nome, int quantidade){
        Produto* produto = estoque.buscarProduto(nome);
        if(produto && produto->getQuantidade() >= quantidade){
            compras.push_back(Produto(nome, produto->getValor(), quantidade));
        }
        else{
            cout << nome << "- Nao encontrado";
        }
    }

    void finalizarCompra() {
        for (auto& produto : compras) {
            estoque.removerProdutos(produto.getNome(), produto.getQuantidade());
        }
        compras.clear();
    }

    void exibirItens()  {
        float valorTotal = 0;
        cout << "Recibo de Compra:\n";
        for (const auto& produto : compras) {
            cout << produto.getNome() << " - Qtd: " << produto.getQuantidade() << " - Valor: R$ "<< fixed << setprecision(2) << produto.getValor() * produto.getQuantidade() << endl;
            valorTotal += produto.getValor() * produto.getQuantidade();
        }
        cout << "Valor Total: R$ " << fixed << setprecision(2) << valorTotal << endl;
    }
};

int main(){
        Estoque estoque;
        estoque.adicionaProduto(Produto("Monitor", 500, 100));
        estoque.adicionaProduto(Produto("Telefone", 150, 300));
        estoque.adicionaProduto(Produto("Teclado", 70, 50));
        estoque.adicionaProduto(Produto("Mouse", 50, 50));

        cout << "\n";
        estoque.exibirEstoque();
        cout << "\n";

        CarrinhoCompras carrinho(estoque);

        carrinho.adicionaCompra("Monitor", 2);
        carrinho.adicionaCompra("Telefone", 5);
        carrinho.adicionaCompra("Teclado", 2);
        
        cout << "\n";
        carrinho.exibirItens();
        cout << "\n";
        carrinho.finalizarCompra();

        cout << "\n";
        estoque.exibirEstoque();
        cout << "\n";

return 0;
}