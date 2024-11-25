package hfsguardadir.objetosgui;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.List;

import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

public class Arvore extends JTree {

    private static final long serialVersionUID = 2994317185652345812L;

    public Arvore(DefaultMutableTreeNode root) {
        super(root);

        setRootVisible(false);
        setShowsRootHandles(true);

        this.getSelectionModel().addTreeSelectionListener(
                new TreeSelectionListener() {
                    @Override
                    public void valueChanged(TreeSelectionEvent evt) {
                        selecaoValorMudou(evt);
                    }
                });
    }

    public void selecaoValorMudou(TreeSelectionEvent evt) {
        this.scrollPathToVisible(evt.getPath());
    }

    public void alterarTextoNode(DefaultMutableTreeNode node, String texto) {
        DefaultTreeModel modelo = (DefaultTreeModel) this.getModel();
        TreePath path = new TreePath(node);
        modelo.valueForPathChanged(path, texto);
    }

    public void alterarTextoNode(TreePath path, String texto) {
        DefaultTreeModel modelo = (DefaultTreeModel) this.getModel();
        modelo.valueForPathChanged(path, texto);
    }

    public void alterarTextoNodeSelecionado(String texto) {
        alterarTextoNode(this.getSelectionPath(), texto);
    }

    public void alterarTextoNodeRaiz(String texto) {
        DefaultMutableTreeNode nodeRaiz = (DefaultMutableTreeNode) this
                .getModel().getRoot();
        alterarTextoNode(nodeRaiz, texto);
    }

    public void excluirNode(DefaultMutableTreeNode node) {
        DefaultTreeModel modelo = (DefaultTreeModel) this.getModel();
        modelo.removeNodeFromParent(node);
    }

    public void limpar(String nomeAbaSelecionada) {
        DefaultMutableTreeNode root = new DefaultMutableTreeNode(
                nomeAbaSelecionada);
        DefaultTreeModel dtm = new DefaultTreeModel(root);
        this.setModel(dtm);
    }

    public void excluirNode(String[] nomes) {
        TreePath path = encontrarCaminhoPorNome(nomes);
        DefaultMutableTreeNode node = (DefaultMutableTreeNode) path
                .getLastPathComponent();
        this.excluirNode(node);
    }

    public TreePath encontrarCaminhoPorNome(String[] nomes) {
        TreeNode root = (TreeNode) this.getModel().getRoot();
        return encontrarCaminho(this, new TreePath(root), nomes, 0, true);
    }

    private TreePath encontrarCaminho(JTree tree, TreePath parent,
            Object[] nodes, int depth, boolean byName) {
        TreeNode node = (TreeNode) parent.getLastPathComponent();
        Object o = node;

        // Se por nome, converte node para string
        if (byName) {
            o = o.toString();
        }

        // Se igual, vai para baixo
        if (o.equals(nodes[depth])) {
            // Se chegou no fim, retorna alvo
            if (depth == nodes.length - 1) {
                return parent;
            }

            // Atravesa filhos
            if (node.getChildCount() >= 0) {
                for (Enumeration<?> e = node.children(); e.hasMoreElements();) {
                    TreeNode n = (TreeNode) e.nextElement();
                    TreePath path = parent.pathByAddingChild(n);
                    TreePath result = encontrarCaminho(tree, path, nodes,
                            depth + 1, byName);
                    // Encontrou um alvo
                    if (result != null) {
                        return result;
                    }
                }
            }
        }

        // Nenhum alvo encontrado
        return null;
    }

	// Se expandir é true, expande todos os nodes na arvore.
    // senão, colapsa todos os nodes na arvore.
    public void expandeTodos(boolean expandir) {
        TreeNode raiz = (TreeNode) this.getModel().getRoot();

        // atravesa a arvore da raiz
        expandeTodos(this, new TreePath(raiz), expandir);

        if (!expandir) {
            this.expandPath(new TreePath(raiz));
        }
    }

    private void expandeTodos(JTree arvore, TreePath pai, boolean expandir) {
        // atravesa o filho
        TreeNode node = (TreeNode) pai.getLastPathComponent();
        if (node.getChildCount() >= 0) {
            for (Enumeration<?> e = node.children(); e.hasMoreElements();) {
                TreeNode n = (TreeNode) e.nextElement();
                TreePath path = pai.pathByAddingChild(n);
                expandeTodos(arvore, path, expandir);
            }
        }

        // Expansao ou colapso deve ser feito de baixo para cima
        if (expandir) {
            arvore.expandPath(pai);
        } else {
            arvore.collapsePath(pai);
        }
    }

    public TreePath getPath(TreeNode node) {
        List<TreeNode> lista = new ArrayList<TreeNode>();

        while (node != null) {
            lista.add(node);
            node = node.getParent();
        }
        Collections.reverse(lista);

        return new TreePath(lista.toArray());
    }

    public TreePath[] getPaths(boolean somenteExpandidos) {
        TreeNode raiz = (TreeNode) this.getModel().getRoot();
        List<TreePath> lista = new ArrayList<TreePath>();
        getPaths(this, new TreePath(raiz), somenteExpandidos, lista);

        return (TreePath[]) lista.toArray(new TreePath[lista.size()]);
    }

    private void getPaths(JTree arvore, TreePath parent, boolean expandido,
            List<TreePath> lista) {
        // Retorna se node não está expandido
        if (expandido && !arvore.isVisible(parent)) {
            return;
        }

        // Adiciona node para a lista
        lista.add(parent);

        // Cria paths para todos os filhos
        TreeNode node = (TreeNode) parent.getLastPathComponent();
        if (node.getChildCount() >= 0) {
            for (Enumeration<?> e = node.children(); e.hasMoreElements();) {
                TreeNode n = (TreeNode) e.nextElement();
                TreePath path = parent.pathByAddingChild(n);
                getPaths(arvore, path, expandido, lista);
            }
        }
    }

}
