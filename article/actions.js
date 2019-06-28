function precRound(n) {
    if (precision == 0)
        return n
    return Math.round(n*precision)/precision
}

function drawTable1() {
    var n = 0
    var text = "<tr><th rowspan=2>Ранг<th rowspan=2>Алгоритм<th colspan=5>Размер данных"
    text += "<tr><th align=center>1'000'000'000<th>100'000'000<th>10'000'000<th>1'000'000<th>100'000"
    for (var sortm in Data1[order[0]][type[0]]) {
        text += "<tr><td align=center>" + (++n).toString() + "<td>" + sortm
        for (var i = 0; i < 5; ++i)
            text += "<td align=right>" + Data1[order[0]][type[0]][sortm][i].toString()
    }
    return text;
}

function DataAvg() {
    var sum = 0
    var cnt = 0
    for (var sortm in Data1[order[0]][type[0]])
        for (var i = 0; i < 5; ++i) {
            sum += Data[order[0]][type[0]][sortm][i]
            cnt++
        }
    return sum/cnt
}

function DataMedian() {
    var vector = []
    for (var sortm in Data1[order[0]][type[0]])
        for (i = 0; i < 5; ++i)
            vector.push(Data[order[0]][type[0]][sortm][i])
    vector.sort(function(a, b){ return a - b })
    return vector[vector.length/2]
}

function DataMin() {
    var min = 1 << 30
    for (var sortm in Data1[order[0]][type[0]])
        for (i = 0; i < 5; ++i)
            if (Data[order[0]][type[0]][sortm][i] < min)
                min = Data[order[0]][type[0]][sortm][i]
    return min
}

function DataMax() {
    var max = 0
    for (var sortm in Data1[order[0]][type[0]])
        for (i = 0; i < 5; ++i)
            if (Data[order[0]][type[0]][sortm][i] > max)
                max = Data[order[0]][type[0]][sortm][i]
    return max
}

function changeOpt1() {
    var pivot = 1  //absolute
    option1 = document.getElementById("options1").value
    if (option1 == 1)  //average
        pivot = DataAvg();
    else if (option1 == 2)  //median
        pivot = DataMedian();
    else if (option1 == 3)  //minimum
        pivot = DataMin();
    else if (option1 == 4)  //maximum
        pivot = DataMax();
    
    for (var sortm in Data1[order[0]][type[0]])
        for (var i = 0; i < 5; ++i)
             Data1[order[0]][type[0]][sortm][i] = precRound(Data[order[0]][type[0]][sortm][i]/pivot)
    document.getElementById("tab1").innerHTML = drawTable1()
}

function changeOpt2() {
    if (document.getElementById("options2").value > 0)
        precision = Math.pow(10, document.getElementById("options2").value);
    else
        precision = 0
    changeOpt1()
}

var duoMode = [0, 0]
var sbuttc = ["1 &#8594; 2", "2 &#8594; 1"]

function types(n, m) {
    if (n == 1) return type[m]
    return order[m]
}

function drawActionTable1() {
    var sv
    var indexValues = [Data1, Data1[order[0]]]
    var text = ""

    for (var i = 0; i < 2; i++) {
        var iv = i.toString()
        text += "<br><button id=sbutt" + iv + " onclick=changeRow(" + iv + ")>" + sbuttc[duoMode[i]] + "</button>:"

        text += "<select id=select" + iv + "0 onchange=changeAction(" + iv + ",0)>"
        for (sv in indexValues[i]) {
            text += "<option value=" + sv
            if (sv == types(i, 0))
                text += " selected"
            text += ">" + sv + "</option>"
        }
        text += "</select>" 

        if (duoMode[i] == 1) {
            text += " vs "
            text += "<select id=select" + iv + "1 onchange=changeAction(" + iv + ",1)>";
            for (sv in indexValues[i]) {
                text += "<option value=" + sv
                if (sv == types(i, 1))
                    text += " selected"
                text += ">" + sv + "</option>"
            }
            text += "</select>"
        }
    }
    var cmpType = ["absolute", "average", "median", "minimum", "maximum"]
    if (duoMode[0] + duoMode[1] == 0) { 
        text += "<select id=options1 onchange=changeOpt1()>"
        for (var i = 0; i < cmpType.length; ++i) {
            text += "<option value=" + i.toString()
            if (i == option1)
                text += " selected"
            text += ">" + cmpType[i] + "</option>"
        }
        text += "</select>"
    }
    return text
}

function changeOptAll() {
    if (duoMode[0] > 0) {
        for (var sortm in Data1[order[0]][type[0]])
            for (var i = 0; i < 5; ++i)
                Data1[order[0]][type[0]][sortm][i] = precRound(Data[order[0]][type[0]][sortm][i]/Data[order[1]][type[0]][sortm][i])
    } else if (duoMode[1] > 0) {
        for (var sortm in Data1[order[0]][type[0]])
            for (var i = 0; i < 5; ++i)
                Data1[order[0]][type[0]][sortm][i] = precRound(Data[order[0]][type[0]][sortm][i]/Data[order[0]][type[1]][sortm][i])
    } else
        changeOpt1()
}

function changeRow(n) {
    if (duoMode[n] == 0)
        duoMode[n] = 1
    else
        duoMode[n] = 0
    for (var i = 0; i < 2; ++i)
        if (i != n)
            duoMode[i] = 0
    document.getElementById("tab1a").innerHTML = drawActionTable1()
    changeOptAll()
    document.getElementById("tab1").innerHTML = drawTable1()
}

function changeAction(n, m) {
    var nms = "select" + n.toString() + m.toString()
    if (n == 1)
        type[m] = document.getElementById(nms).value
    else
        order[m] = document.getElementById(nms).value
    changeOptAll()
    document.getElementById("tab1").innerHTML = drawTable1()
}

