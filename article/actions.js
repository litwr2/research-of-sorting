function precRound(n) {
    if (precision == 0)
        return n
    return Math.round(n*precision)/precision
}

function drawTable1() {
    var n = 0;
    var sortm;
    var text = "<tr><th rowspan=2>Ранг<th rowspan=2>Алгоритм<th colspan=5>Размер данных";
    text += "<tr><th align=center>1'000'000'000<th>100'000'000<th>10'000'000<th>1'000'000<th>100'000";
    for (sortm in Data1[order][type]) {
        text += "<tr><td align=center>" + (++n).toString() + "<td>" + sortm
        for (var i = 0; i < 5; ++i)
            text += "<td align=right>" + Data1[order][type][sortm][i].toString()
    }
    return text;
}

function DataAvg() {
    var sum = 0
    var cnt = 0
    var sortm
    for (sortm in Data1[order][type])
        for (var i = 0; i < 5; ++i) {
            sum += Data[order][type][sortm][i]
            cnt++
        }
    return sum/cnt
}

function DataMedian() {
    var vector = [];
    var sortm
    for (sortm in Data1[order][type])
        for (i = 0; i < 5; ++i)
            vector.push(Data[order][type][sortm][i])
    vector.sort(function(a, b){ return a - b })
    return vector[vector.length/2]
}

function DataMin() {
    var min = 1 << 30
    var sortm
    for (sortm in Data1[order][type])
        for (i = 0; i < 5; ++i)
            if (Data[order][type][sortm][i] < min)
                min = Data[order][type][sortm][i]
    return min
}

function DataMax() {
    var max = 0
    var sortm
    for (sortm in Data1[order][type])
        for (i = 0; i < 5; ++i)
            if (Data[order][type][sortm][i] > max)
                max = Data[order][type][sortm][i]
    return max
}

function changeOpt1() {
    var pivot = 1;  //absolute
    if (document.getElementById("options1").value == 1)  //average
        pivot = DataAvg();
    else if (document.getElementById("options1").value == 2)  //median
        pivot = DataMedian();
    else if (document.getElementById("options1").value == 3)  //minimum
        pivot = DataMin();
    else if (document.getElementById("options1").value == 4)  //maximum
        pivot = DataMax();
    
    var sortm;
    for (sortm in Data1[order][type])
        for (i = 0; i < 5; ++i)
             Data1[order][type][sortm][i] = precRound(Data[order][type][sortm][i]/pivot);
    document.getElementById("tab1").innerHTML = drawTable1()
}

function changeOpt2() {
    if (document.getElementById("options2").value > 0)
        precision = Math.pow(10, document.getElementById("options2").value);
    else
        precision = 0
    changeOpt1()
}

var selectButtons = [0, 0, 0];
var sbuttc = ["1 &#8594; 2", "2 &#8594; 1"];

function drawActionTable1() {
    var i;
    var sv;
    var indexValues = [Data1[order][type], Data1, Data1[order]];
    var text = "<tr><th><th>";

    for (i = 0; i < 3; i++) {
        var iv = i.toString();
        text += "<tr><td><button id=sbutt" + iv + " onclick=changeRow(" + iv + ")>" + sbuttc[selectButtons[i]] + "</buttons>";
        text += "<td align=center><select id=select" + iv + "0 onchange=changeMethodLeft(" + iv + ")>";
        for (sv in indexValues[i])
            text += "<option value=" + sv + ">" + sv + "</option>";
        text += "</select>";
        if (selectButtons[i] == 1) {
            text += " vs ";
            text += "<select id=select" + iv + "1 onchange=changeMethodRight(" + iv + ")>";
            for (sv in indexValues[i])
                text += "<option value=" + sv + ">" + sv + "</option>";
            text += "</select>";
        }
    }
    return text;
}

function changeRow(n) {
    var i;
    if (selectButtons[n] == 0) {
        selectButtons[n] = 1;
    } else {
        selectButtons[n] = 0;
    }
    for (i = 0; i < 3; ++i)
        if (i != n)
            selectButtons[i] = 0;
    document.getElementById("tab1a").innerHTML = drawActionTable1();
    document.getElementById("tab1").innerHTML = drawTable1();
}

