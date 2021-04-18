const exec = require('child_process').exec;
const fs = require('fs');

const execAsync = (command) => {
  return new Promise((resolve, reject) => {
    exec(command, (err, output, error) => {
      if (err) {
        console.log(error);
        reject();
      }

      console.log(output);
      resolve();
    });
  });
}

desc('Build all apps.');
task('default', ['BuildWebClient', 'BuildServer'], () => { });

desc('Build WebClient.');
task('BuildWebClient', () => {
  return new Promise(async (resolve, reject) => {
    try {
      fs.accessSync('WebClient/build', fs.constants.F_OK);
      fs.rmdirSync('WebClient/build', { force: true, recursive: true });
    } catch (e) {
      console.log('No directory to delete');
    }

    try {
      await execAsync('cd WebClient && npm ci && npm run build');
      resolve()
    } catch (e) {
      reject(e);
    }
  });
});

desc('Build Server.');
task('BuildServer', () => {
  return new Promise(async (resolve, reject) => {
    try {
      await execAsync('cd Server && npm ci && npm run build');
      resolve()
    } catch (e) {
      reject(e);
    }
  });
});
