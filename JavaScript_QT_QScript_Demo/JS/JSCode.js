function func(a,b) {
    var a1=a;
    var a2=b;
    return a1+a2;
}

function up2(){
    var x=pm.GetMessage();

    var text="SetMessage the Text !";
    pm.SetMessage(text);
    var y=pm.GetMessage();

    var z=x+"\n"+y;
    return z;
}
