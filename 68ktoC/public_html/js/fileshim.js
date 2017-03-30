/* global FileReaderJS */

function noop() {}

function parsefile(e, file) {
    var filedump = e.target.result;
    var output = new Uint8Array(filedump);
    main(output);
}
  
  var opts = {
            dragClass: "drag",
            accept: false,
            readAsDefault: 'ArrayBuffer',
            readAsMap: {},
            on: {
                loadstart: noop,
                progress: noop,
                load: noop,
                abort: noop,
                error: noop,
                loadend: parsefile,
                skip: noop,
                groupstart: noop,
                groupend: noop,
                beforestart: noop
            }
};
  
function initfiledriver() {
    FileReaderJS.setupInput(document.getElementById('fileinput'), opts);
}
  
window.onload = initfiledriver;
