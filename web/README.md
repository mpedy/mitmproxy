# Quick Start

- Install mitmproxy as described in [`../CONTRIBUTING.md`](../CONTRIBUTING.md)
- Run `node --version` to make sure that you have at least Node.js 18 or above. If you are on **Ubuntu <= 22.04**, you
  need to
  [upgrade](https://github.com/nodesource/distributions/blob/master/README.md#installation-instructions).
- Run `cd mitmproxy/web` to change to the directory with package.json
- Run `npm install` to install dependencies
- Run `npm start` to start live-compilation
- Run `mitmweb` after activating your Python virtualenv (see [`../CONTRIBUTING.md`](../CONTRIBUTING.md)).

## Testing

- Run `npm test` to run the test suite.

## Code formatting

- Run `npm run prettier` to format your code. You can also integrate prettier into your editor, see https://prettier.io/docs/en/editors.html

## Architecture

There are two components:

- Server: [`mitmproxy/tools/web`](../mitmproxy/tools/web)

- Client: `web`

## Contributing

We very much appreciate any (small) improvements to mitmweb. Please do *not* include the compiled assets in
[`mitmproxy/tools/web/static`](https://github.com/mitmproxy/mitmproxy/tree/main/mitmproxy/tools/web/static)
in your pull request. Refreshing them on every commit would massively increase repository size. We will update these
files before every release.

## Developer Tools

- `npm start` supports live-reloading if you install a matching
  [browser extension](http://livereload.com/extensions/).
- You can debug application state using the
  [React DevTools](https://reactjs.org/blog/2019/08/15/new-react-devtools.html) and
  [Redux DevTools](https://github.com/reduxjs/redux-devtools) browser extensions.


# GUIDA

I posti per aggiungere una nuova colonna sono diversi. Vi è un codice Python che gestisce quali colonne siano da aggiungere e quali tralasciare, si trova al percorso "mitmproxy/tools/web/webaddons.py". Qui è possibile scegliere una lista di colonne da poter aggiungere alla UI, è bene selezionarne anche di più perché le colonne stesse (le FlowColumn) hanno poi una variabile per farle apparire o scomparire.

Una volta aggiunte le colonne nel Python, le andiamo a scrivere proprio nel file FlowColumns.tsx al percorso web/src/js/components/FlowTable/FlowColumns.tsx. Qui è presente una interface, la FlowColumn, a cui ho aggiunto la variabile invisible?: boolean. Questa variabile è responsabile di far visualizzare o meno le colonne create: infatti, in FlowRow.tsx e FlowTableHead.tsx vengono importate tutte le colonne (c'è un import * as columns from FlowColumn, quindi tutti gli export di FlowColumn devono essere delle colonne), e in seguito vengono filtrate per filter((x)=> x.invisible == undefined). Questo quindi permette a qualsiasi FlowColumn che non abbia impostato il valore di invisible ad essere visualizzata. Viceversa, se una FlowColumn avesse il campo invisible = "si" | 1 | true | "", allora la colonna sarebbe nascosta (sia nell'intestazione, thead, sia nel corpo, tbody. Vedi i due file FlowTableHead e FlowRow menzionati prima).

Per far funzionare il tutto, occorre lanciare con il comando:
``venv/Scripts/mitmweb_my.exe -s ..\SystemProxy\myaddon.py``
ci vuole, insomma, il mio addon per far funzionare il tutto.

## Compilazione live
Ho dovuto installare il progetto come editabile con "venv/Script/pip install -e .\[dev\]" nel main prnicipale del progetto. In questo modo il codice Python è più facilmente editabile (non ho ancora capito cosa significa). Dopodiché se vado in radice/web e lancio da qui il comando ``npm start`` mi parte gulp. Questo programma, per come è stato scritto, non lancia eccezioni in caso ci fosse qualcosa di storto, ma finisce silenziosamente, per cui ho dovuto aggiungere queste righe

``
// Evento "error" in caso di errore
stream.on('error', function (err) {
    console.error('Errore nel processamento di esbuild:', err);
});
``
per controllare che effettivamente stia andando tutto per il meglio e non ci siano intoppi (le ho messe solo sul programma script_dev perché mi serviva solo questo per il momento). Una volta che gira il tutto, il client e la sua UI sono modificabili, il codice Python deve invece essere fatto ripartire (ahh! Forse è questo il -e del pip, cioè non lo installa ma lo prende come fosse installato, quindi se modifico il sorgente si modifica anche il programma "installato" senza dover fare una nuova installazione!).

Attenzione per il file pyproject.toml : l'ho modificato in maniera tale che generasse i 3 eseguibili (mitmproxy, mitmdump e mitmweb) con il suffisso "_my", in modo da distinguerli con quelli installati a livello di sistema

## Link utili:

[Aggiunta nuova colonna #7039](https://github.com/mitmproxy/mitmproxy/pull/7039/files)
[Errore per script_dev, me ne sono accorto da qui che il suo finiva correttamente mentre il mio rimaneva appeso in "Started ... "](https://github.com/mitmproxy/mitmproxy/discussions/6664)
[Comandi PowerShell per impostazioni proxy di sistema](https://www.techcrafters.com/portal/en/kb/articles/powershell-comprehensive-guide-to-configuring-proxy-settings-on-windows#Enabling_the_Proxy)
[Building dei programmi - 1](https://stackoverflow.com/questions/62334867/how-are-the-pre-compiled-mitmproxy-binaries-actually-built)
[Building dei programmi - 2](https://github.com/mitmproxy/mitmproxy/blob/bbc2cf331a4ab180001668bf4b51eeec505e01ab/.github/workflows/main.yml#L84-L111)
[Building dei programmi - 3](https://github.com/mitmproxy/mitmproxy/blob/bbc2cf331a4ab180001668bf4b51eeec505e01ab/release/cibuild.py#L372-L450)