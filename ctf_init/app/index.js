const express=require('express');
const app=express();
const routes=require('./routes');
const nunjucks=require('nunjucks');
const cookieParser = require('cookie-parser');

app.use(express.urlencoded({extended: true}));
app.use(express.json());
app.use(cookieParser());

nunjucks.configure('views', {
    autoescape: true,
    express: app
});
app.set('views','./views');
app.use(routes);

app.all('*', (req, res) => {
    return res.status(404).send('404 page not found');
});

app.listen(1337, () => console.log('Listening on port 1337'));
