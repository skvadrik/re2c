function svgAddBar(fig,x,y,w,h,color){
    var bar = document.createElementNS("http://www.w3.org/2000/svg","rect");
    bar.x.baseVal.value = x;
    bar.y.baseVal.value = y;
    bar.width.baseVal.value = w;
    bar.height.baseVal.value = h;
    bar.style.fill = color;
    fig.appendChild(bar);
}
function svgAddHgridLine(fig,x,y,w,color,contents){
    var bar = document.createElementNS("http://www.w3.org/2000/svg","rect");
    bar.x.baseVal.value = x;
    bar.y.baseVal.value = y;
    bar.width.baseVal.value = w;
    bar.height.baseVal.value = 1;
    bar.style.fill = color;
    fig.appendChild(bar);
    var text = document.createElementNS("http://www.w3.org/2000/svg","text");
    text.setAttributeNS(null,"font-size","7pt");
    text.textContent = contents;
    fig.appendChild(text);
    var wt = text.getComputedTextLength();
    text.setAttributeNS(null,"x",x-wt);
    text.setAttributeNS(null,"y",y);
}
function svgAddLabel(fig,x,y,contents,fontsize){
    var text = document.createElementNS("http://www.w3.org/2000/svg","text");
    text.setAttributeNS(null,"x",x);
    text.setAttributeNS(null,"y",y);
    text.setAttributeNS(null,"font-size",fontsize);
    text.textContent = contents;
    fig.appendChild(text);
}
function svgAddLine(fig,x1,y1,x2,y2,w,color){
    var line = document.createElementNS("http://www.w3.org/2000/svg","line");
    line.x1.baseVal.value = x1;
    line.y1.baseVal.value = y1;
    line.x2.baseVal.value = x2;
    line.y2.baseVal.value = y2;
    line.setAttributeNS(null,"stroke",color);
    line.setAttributeNS(null,"stroke-width",w);
    fig.appendChild(line);
}
function svgAddVtick(fig,x,y){
    var line = document.createElementNS("http://www.w3.org/2000/svg","line");
    line.x1.baseVal.value = x;
    line.y1.baseVal.value = y;
    line.x2.baseVal.value = x;
    line.y2.baseVal.value = y+5;
    line.setAttributeNS(null,"stroke","darkgray");
    line.setAttributeNS(null,"stroke-width",1);
    fig.appendChild(line);
}
function svgAddLegend(svg,x,text,color,y){
    svgAddBar(svg,x,y,20,2,color);
    svgAddLabel(svg,x+25,y+5,text,"7pt");
}
var xAxisName = "text repetitions";
var yAxisName = "toks/msec";
var curvesLegend = "";
function svgChart(id,re,text,data){
    var svg = document.getElementById(id);

    var xorig = 60;
    var yorig = 320;
    var max = 0;
    for (var i = 1; i < data.length; i++){
        for (var j = 1; j < data[i].length; j++){
            if (data[i][j] > max) max = data[i][j];
        }
    }
    // draw horizontal grid
    /*
    var scale = 1;
    for (var i = 0; i < 6; i++){
        if (max < scale) break;
        scale *= 10;
    }
    var scale10 = Math.floor(scale/10);
    var scale = 1;
    for (var i = 0; i <= 10; i++){
        if (max < scale) break;
        scale += scale10;
    }
    var factscale = Math.floor(scale/10);
    if (factscale == 0) factscale = 1;
    */

    var logm = Math.floor(Math.log10(max));
    var tenpow = Math.pow(10,logm);
    var higrid = Math.floor(max/tenpow + 1)*tenpow;

    for (var i = 0; i <= 10; i++){
//        svgAddHgridLine(svg,xorig,yorig-i*30,660,"darkgray",Math.floor(i * factscale));
//        svgAddHgridLine(svg,xorig,yorig-i*30,660,"darkgray",Math.floor(i * (higrid/10)));
        svgAddHgridLine(svg,xorig,yorig-i*30,660,"darkgray",i * higrid/10);
    }

    // draw x axis labels
    for (var i = 0; i < data[0].length; i++){
        svgAddLabel(svg,xorig+50*i,yorig+15,data[0][i],"7pt");
        svgAddVtick(svg,xorig+50*i,yorig);
    }
    svgAddLabel(svg,xorig+50*data[0].length,yorig+20,xAxisName,"7pt");
    svgAddLabel(svg,5,yorig-287,yAxisName,"7pt");

    // legend for lines
    for (var i = 1; i < data.length; i++){
        var lab = data[i][0].split("|");
        svgAddLegend(svg,730+xorig,lab[0],lab[1],20+(i*30));
    }

    if (curvesLegend != ""){
        svgAddLabel(svg,730+xorig,30,curvesLegend,"8pt");
    }

    // title
    if (text.length > 0){
        svgAddLabel(svg,xorig,370,"RE: "+re+"\u2001\u2001\u2001 text: "+text,"11pt");
    } else {
        svgAddLabel(svg,xorig,370,re,"11pt");
    }

    // draw the lines
    // var p = (scale/10)/30;
    // var p = factscale/30;
    var p = (higrid/10)/30;
    for (var i = 1; i < data.length; i++){
        var serie = data[i];
        for (var j = 1; j < serie.length-1; j++){
            if (isNaN(serie[j])) break;
            if (isNaN(serie[j+1])) break;
            var height1 = serie[j] / p;
            var height2 = serie[j+1] / p;
            var lab = data[i][0].split("|");
            svgAddLine(svg,xorig+50*j,yorig-height1,
                xorig+50*(j+1),yorig-height2,2,lab[1]);
        }
    }
}
