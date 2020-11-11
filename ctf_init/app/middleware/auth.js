const jwt=require('../src/jwt');

module.exports= async (req,res,next)=> {
    try{
        if(req.cookies.token===undefined||req.cookies.token==="") return res.redirect('/auth');
        let payload = await jwt.verify(req.cookies.token);
        req.data={
            username:payload.username
        }
        next();
    }catch(e){
        res.status(500).send("500 Internal Server Error")
    }
}