import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

public class FIFAFileLoaderGUI extends JFrame {

    // Campos de texto para busca
    private JTextField idField;
    private JTextField idadeField;
    private JTextField nomeJogadorField;
    private JTextField nacionalidadeField;
    private JTextField nomeClubeField;

    // Painel para os campos de busca
    private JPanel buscaPanel;
    // Painel para informações do arquivo carregado
    private JPanel infoPanel;
    // Painel para os botões de funções
    private JPanel botoesPanel;

    public FIFAFileLoaderGUI() {
        setTitle("Trabalho Final - SSC0103");
        setSize(600, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        // Centraliza a janela no monitor
        setLocationRelativeTo(null);

        // Criando o menu
        JMenuBar menuBar = new JMenuBar();
        JMenu arquivoMenu = new JMenu("Arquivo");

        // Item do menu para carregar arquivo
        JMenuItem carregarArquivoItem = new JMenuItem("Carregar Arquivo");

        // Adicionando os itens ao menu
        arquivoMenu.add(carregarArquivoItem); // Adiciona o novo item de menu "Carregar Arquivo"

        // Adicionando o menu à barra de menus
        menuBar.add(arquivoMenu);

        // Definindo a barra de menus para a janela
        setJMenuBar(menuBar);

        // ActionListener para carregar arquivo
        carregarArquivoItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                carregarArquivo();
            }
        });

        // Exibindo a janela
        setVisible(true);

        // Painel de Busca e funções visiveis apenas quando se carrega o arquivo
        criaPainelBusca(false);
        botoesFuncoes(false);
    }

    // Método para carregar o arquivo BIN selecionado
    private void carregarArquivo() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File(".")); // Diretório inicial

        int result = fileChooser.showOpenDialog(this);

        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();

            // Verifica se o arquivo selecionado é um arquivo bin
            if (selectedFile.getName().endsWith(".bin")) {
                // Chama o método para processar o arquivo bin
                processarBIN(selectedFile);
            } else {
                JOptionPane.showMessageDialog(this, "Por favor, selecione um arquivo bin.");
            }
        }
    }

    // Método para processar o arquivo BIN selecionado
    private void processarBIN(File arquivoBIN) {
        // Limpa o painel de busca
        buscaPanel.setVisible(false);
        botoesPanel.setVisible(false);

        // Cria o painel de informações do arquivo carregado
        criaInfoPanel("Arquivo bin selecionado: " + arquivoBIN.getName());

        // Adiciona o painel de informações à janela
        JPanel mainPanel = (JPanel) getContentPane().getComponent(0);
        mainPanel.add(infoPanel, BorderLayout.CENTER);
        mainPanel.revalidate();
        mainPanel.repaint();

        // Após processar o arquivo, inicializa o painel de busca e os botoes de funcoes
        buscaPanel.setVisible(true);
        botoesPanel.setVisible(true);

        // envia para o servidor em Python o nome do arquivo
        String nomeArquivo = "2" + " " + arquivoBIN.getName() + "\0";
        enviarParaServidor(nomeArquivo);
        // depois de enviar o nome do arquivo, ele iria receber a lista de todos os jogadores abaixo
    }

    private void criaPainelBusca(boolean visivel) {
        // Painel para os campos de busca
        buscaPanel = new JPanel(new GridLayout(5, 2, 10, 10)); // GridLayout com 5 linhas e 2 colunas
        buscaPanel.setBorder(BorderFactory.createTitledBorder("Insira Os Dados e Depois Selecione a Função"));

        // Labels e campos de texto para os critérios de busca
        buscaPanel.add(new JLabel("ID (inteiro, 4 bytes):"));
        idField = new JTextField();
        buscaPanel.add(idField);

        buscaPanel.add(new JLabel("Idade (inteiro, 4 bytes):"));
        idadeField = new JTextField();
        buscaPanel.add(idadeField);

        buscaPanel.add(new JLabel("Nome do Jogador:"));
        nomeJogadorField = new JTextField();
        buscaPanel.add(nomeJogadorField);

        buscaPanel.add(new JLabel("Nacionalidade:"));
        nacionalidadeField = new JTextField();
        buscaPanel.add(nacionalidadeField);

        buscaPanel.add(new JLabel("Nome do Clube:"));
        nomeClubeField = new JTextField();
        buscaPanel.add(nomeClubeField);

        // Painel principal da janela
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.add(buscaPanel, BorderLayout.NORTH);

        // Adicionando o painel principal à janela
        add(mainPanel);

        // Define a visibilidade do painel de busca
        buscaPanel.setVisible(visivel);
    }

    // Método auxiliar para verificar se um campo corresponde ao critério de busca
    private boolean matchField(String campo, String valorBuscado) {
        return valorBuscado.isEmpty() || campo.toLowerCase().contains(valorBuscado.toLowerCase());
    }

    // Método para criar os botões de funções (Buscar Jogador, Inserir Jogador, Remover Jogador)
    private void botoesFuncoes(boolean visivel) {
        botoesPanel = new JPanel(new GridLayout(1, 3, 10, 10)); // GridLayout com 1 linha e 3 colunas

        JButton buscarJogadorButton = new JButton("Buscar Jogador");
        JButton alterarJogadorButton = new JButton("Alterar Jogador");
        JButton removerJogadorButton = new JButton("Remover Jogador");

        buscarJogadorButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                buscarJogadores();
            }
        });

        alterarJogadorButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                alterarJogador();
            }
        });

        removerJogadorButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                removerJogador();
            }
        });

        // Adicionando os botões ao painel de botões
        botoesPanel.add(buscarJogadorButton);
        botoesPanel.add(alterarJogadorButton);
        botoesPanel.add(removerJogadorButton);

        // Adicionando o painel de botões à janela
        JPanel mainPanel = (JPanel) getContentPane().getComponent(0);
        mainPanel.add(botoesPanel, BorderLayout.SOUTH);

        // Define a visibilidade dos botões
        botoesPanel.setVisible(visivel);
    }

    // Método para criar o painel de informações do arquivo carregado
    private void criaInfoPanel(String info) {
        infoPanel = new JPanel();
        infoPanel.setBorder(BorderFactory.createTitledBorder("Informações do Arquivo Carregado"));
        infoPanel.setLayout(new BoxLayout(infoPanel, BoxLayout.Y_AXIS));

        JLabel infoLabel = new JLabel(info);
        infoLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        infoPanel.add(infoLabel);
    }

    // Método para realizar a busca com os critérios fornecidos
    private void buscarJogadores() {
        String comando = "3 ";
        comando = comando + preencherComando();
        limparFields();

        System.out.println("Buscando jogadores...");

        enviarParaServidor(comando);
        // aqui ele enviaria o comando para buscar o jogador com os campos e mostraria ele para selecionar
    }

    // Método para realizar a inserção de jogador
    private void alterarJogador() {
        String comando = "1 ";
        comando = comando + preencherComando();
        limparFields();

        System.out.println("Inserindo jogador...");
        
        enviarParaServidor(comando);
        // aqui voce abriria uma nova tela para adicionar os dados a serem alterados
    }

    // Método para realizar a remoção de jogador
    private void removerJogador() {
        String comando = "3 ";
        comando = comando + preencherComando();
        limparFields();

        System.out.println("Removendo jogador...");
        
        enviarParaServidor(comando);
        // aqui você removeria o jogador
    }

    // Faz uma string para enviar para o servidor em python para realizar as funções
    private String preencherComando() {
        String id = idField.getText();
        String idade = idadeField.getText();
        String nomeJogador = nomeJogadorField.getText();
        String nacionalidade = nacionalidadeField.getText();
        String nomeClube = nomeClubeField.getText();

        String comando = id + " " + idade + " " + nomeJogador + " " + nacionalidade + " " + nomeClube + "\0";
        return comando;
    }

    // Limpar os campos após enviar os dados
    private void limparFields() {
        idField.setText("");
        idadeField.setText("");
        nomeJogadorField.setText("");
        nacionalidadeField.setText("");
        nomeClubeField.setText("");
    }

    // Método para conectar, enviar e receber os dados para o servidor Python
    private void enviarParaServidor(String dados) {
        String host = "localhost";
        int port = 12345;

        try (Socket socket = new Socket(host, port);
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

            // Envia os dados para o servidor
            out.println(dados);

            // Recebe resposta do servidor
            String resposta = in.readLine();
            System.out.println("Resposta do servidor: " + resposta);

        } catch (UnknownHostException e) {
            System.err.println("Host desconhecido: " + host);
        } catch (IOException e) {
            System.err.println("Erro de I/O para o host " + host);
        }
    }
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new FIFAFileLoaderGUI();
            }
        });
    }
}
