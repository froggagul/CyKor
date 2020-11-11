const express=require('express')
const router=express.Router()
const DB=require('../src/database.js')
const jwt=require('../src/jwt')
const Auth=require('../middleware/auth')


router.get("/",Auth, async (req,res,next)=>{

    try {
        if (req.cookies.token === undefined) {
            return res.redirect('/auth');
        }
        let user = await DB.getUser(req.data.username);
        if (user === undefined) {
            return res.send(`user ${req.data.username} doesn't exist in database.`);
        }
        return res.render('index.html', { user });
    }
     catch (error) {
        return next();
    }
})

router.get('/logout', (req, res) => {
    res.clearCookie('token');
    return res.redirect('/auth');
});

router.get('/auth', async (req, res) => {
    res.render('auth.html',{query:req.query});
})

router.post('/auth', async (req,res)=>{
    const { username,password }=req.body;
    if(req.body.register !== undefined){
        let checkRegister = await DB.checkUser(username);
        if (!checkRegister){
            return await res.redirect('/auth?error=User already exists!')
        }
        else if(username.trim().length===0 || password.trim().length===0){
            return await res.redirect('/auth')
        }
        
        DB.createUser(username,password);
        return await res.redirect('/auth?error=Successfully Registered&type=success')
    }

    let checkLogin = await DB.login(username,password);
    if(!checkLogin){
        return res.redirect('/auth?error=Invalid Username or Password')
    }
    let token = await jwt.sign({
        username: username.replace(/'/g, "\'\'").replace(/"/g, "\"\"")
    })
    res.cookie('token', token);
    return await res.redirect('/');
})

module.exports = router;