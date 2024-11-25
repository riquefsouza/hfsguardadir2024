// main.js
const { app, BrowserWindow, Menu, dialog } = require('electron');

function createWindow() {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true
    }
  });

  win.loadFile('index.html');
}

const menuTemplate = [
  {
    label: 'File',
    submenu: [
      {
        label: 'Sobre',
        click: () => {
          dialog.showMessageBox({
            type: 'info',
            title: 'Sobre',
            message: 'Hello World Application\nVersão 1.0\nDesenvolvido por Henrique Figueiredo de Souza',
            buttons: ['OK']
          });
        }
      },
      {
        label: 'Sair',
        click: () => {
          app.quit();
        }
      }
    ]
  }
];

app.whenReady().then(() => {
  const menu = Menu.buildFromTemplate(menuTemplate);
  Menu.setApplicationMenu(menu);

  createWindow();
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});
