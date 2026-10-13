from pathlib import Path
import re
import math
import xml.etree.ElementTree as ET

BASE = Path(__file__).resolve().parents[1]
FIGURES = BASE / 'report' / 'figures'
TITLES = {
    'linear': 'Линейный поиск',
    'classic': 'Классический бинарный поиск',
    'branchless': 'Бинарный поиск без ветвления',
    'recursive': 'Рекурсивный бинарный поиск',
}


def label(text):
    text = re.sub(r'\\textsf\{([^{}]*)\}', r'\1', text)
    return text.replace(r'\_', '_').replace('\\\\', '\n').replace('$', '').strip()


def diagram(name):
    source = (FIGURES / f'{name}.tex').read_text(encoding='utf-8')
    factor_y = .96 if name == 'branchless' else 1
    nodes = {}
    pattern = r'\\node\[(.*?)\]\s*\((\w+)\)\s*at\s*\(([-\d.]+),([-\d.]+)\)\s*\{(.*?)\};'
    for match in re.finditer(pattern, source, re.S):
        style, key, x, y, text = match.groups()
        text = label(text)
        kind = style.split(',')[0]
        width = 220
        height = max(55, 22 * len(text.splitlines()) + 12)
        if kind.startswith('decision'):
            height = 120 if kind == 'decisiontall' else 100
        if kind == 'inputnote':
            width, height = 255, 100
        if key in ('lcall', 'rcall'):
            width = 225
        nodes[key] = dict(x=float(x)*50, y=-float(y)*50*factor_y,
                          w=width, h=height, text=text, kind=kind)
    minimum_x = min(n['x']-n['w']/2 for n in nodes.values())
    # Leave room for the return paths on either side of the blocks.
    dx, dy = max(60-minimum_x, 450), 90
    def point(x, y):
        return float(x)*50+dx, -float(y)*50*factor_y+dy
    model = ET.Element('mxGraphModel', dx='1200', dy='1600', grid='1', gridSize='10',
                       guides='1', tooltips='1', connect='1', arrows='1', fold='1',
                       page='1', pageScale='1', pageWidth='1100', pageHeight='1500',
                       math='0', shadow='0')
    root = ET.SubElement(model, 'root')
    ET.SubElement(root, 'mxCell', id='0')
    ET.SubElement(root, 'mxCell', id='1', parent='0')
    for key, n in nodes.items():
        kind = n['kind']
        style = 'whiteSpace=wrap;html=0;fontFamily=Arial;fontSize=16;fontColor=#000000;strokeColor=#000000;fillColor=#FFFFFF;strokeWidth=1;align=center;verticalAlign=middle;spacing=4;'
        if kind == 'term':
            style += 'rounded=1;arcSize=50;absoluteArcSize=1;'
        elif kind.startswith('decision'):
            style += 'shape=rhombus;perimeter=rhombusPerimeter;fontSize=15;'
        elif kind == 'inputnote':
            style += 'strokeColor=none;fillColor=none;fontSize=15;'
        elif key in ('lcall', 'rcall'):
            style += 'shape=mxgraph.flowchart.predefined_process;fontSize=14;'
        else:
            style += 'rounded=0;'
        cell = ET.SubElement(root, 'mxCell', id=key, value=n['text'], style=style, vertex='1', parent='1')
        ET.SubElement(cell, 'mxGeometry', x=str(n['x']+dx-n['w']/2), y=str(n['y']+dy-n['h']/2),
                      width=str(n['w']), height=str(n['h']), attrib={'as':'geometry'})
    anchor = {'north':(0.5,0), 'south':(0.5,1), 'west':(0,0.5), 'east':(1,0.5)}
    counter = 0
    junctions = {}
    def endpoint(token):
        if ',' in token:
            pos = point(*token.split(','))
            if pos not in junctions:
                key = f'junction{len(junctions)}'
                junctions[pos] = key
                cell = ET.SubElement(root, 'mxCell', id=key, value='',
                    style='ellipse;strokeColor=none;fillColor=none;resizable=0;', vertex='1', parent='1')
                ET.SubElement(cell, 'mxGeometry', x=str(pos[0]-.5), y=str(pos[1]-.5), width='1', height='1', attrib={'as':'geometry'})
            return junctions[pos], None, pos
        key, _, side = token.partition('.')
        n = nodes[key]
        xy = anchor.get(side, (.5,.5))
        pos = (n['x']+dx+(xy[0]-.5)*n['w'], n['y']+dy+(xy[1]-.5)*n['h'])
        return key, anchor.get(side), pos
    # Ignore the two internal lines of recursive process symbols: the native
    # draw.io predefined-process shape supplies those lines itself.
    for match in re.finditer(r'\\draw(?:\[([^\]]*)\])?\s*(.*?);', source, re.S):
        options, path = match.groups()
        if path.lstrip().startswith('([xshift='):
            continue
        edge_label = ''
        labels = re.findall(r'node\[[^\]]*\]\{([^{}]*)\}', path)
        if labels:
            edge_label = labels[0]
        path = re.sub(r'node\[[^\]]*\]\{[^{}]*\}', '', path)
        tokens = re.findall(r'\((\w+(?:\.(?:north|south|east|west))?|[-\d.]+,[-\d.]+)\)', path)
        if len(tokens) < 2:
            raise ValueError(f'Unparsed path: {path}')
        operators = re.findall(r'--|\-\||\|\-', path)
        points = [endpoint(t) for t in tokens]
        waypoints = []
        for i, op in enumerate(operators):
            a, b = points[i][2], points[i+1][2]
            if op == '-|': waypoints.append((b[0], a[1]))
            elif op == '|-': waypoints.append((a[0], b[1]))
            if i+1 < len(points)-1: waypoints.append(b)
        source_id, source_anchor, _ = points[0]
        target_id, target_anchor, _ = points[-1]
        style = 'edgeStyle=segmentEdgeStyle;rounded=0;html=0;strokeColor=#000000;strokeWidth=1;fontFamily=Arial;fontSize=15;fontColor=#000000;labelBackgroundColor=#FFFFFF;'
        style += 'endArrow=classic;endFill=1;' if options == 'arrow' else 'endArrow=none;'
        if options == 'dashed': style += 'dashed=1;'
        if source_anchor:
            style += f'exitX={source_anchor[0]};exitY={source_anchor[1]};exitDx=0;exitDy=0;'
        if target_anchor:
            style += f'entryX={target_anchor[0]};entryY={target_anchor[1]};entryDx=0;entryDy=0;'
        counter += 1
        cell = ET.SubElement(root, 'mxCell', id=f'edge{counter}', value=edge_label, style=style,
                             edge='1', parent='1', source=source_id, target=target_id)
        geo = ET.SubElement(cell, 'mxGeometry', relative='1', attrib={'as':'geometry'})
        if waypoints:
            arr = ET.SubElement(geo, 'Array', attrib={'as':'points'})
            for x,y in waypoints: ET.SubElement(arr, 'mxPoint', x=str(x), y=str(y))
        if edge_label:
            ET.SubElement(geo, 'mxPoint', x='0', y='-14', attrib={'as':'offset'})
    return model, len(nodes), counter


def save(path, pages):
    document = ET.Element('mxfile', host='app.diagrams.net', version='26.0.0', type='device', compressed='false')
    for name, model in pages:
        page = ET.SubElement(document, 'diagram', id=name, name=TITLES[name])
        page.append(model)
    ET.indent(document)
    ET.ElementTree(document).write(path, encoding='utf-8', xml_declaration=True)
    # Check that each native connector points to existing editable cells.
    parsed = ET.parse(path)
    for page in parsed.findall('diagram'):
        cells = page.findall('./mxGraphModel/root/mxCell')
        ids = [cell.get('id') for cell in cells]
        assert len(ids) == len(set(ids))
        for cell in cells:
            if cell.get('edge'):
                assert cell.get('source') in ids and cell.get('target') in ids
        for geo in page.findall('.//mxGeometry'):
            for prop in ('x', 'y', 'width', 'height'):
                if geo.get(prop): assert math.isfinite(float(geo.get(prop)))


def main():
    pages = []
    for name in TITLES:
        model, nodes, edges = diagram(name)
        save(FIGURES / f'{name}.drawio', [(name, model)])
        pages.append((name, model))
        print(f'{name}: {nodes} blocks, {edges} connectors')
    save(FIGURES / 'search_algorithms.drawio', pages)


if __name__ == '__main__':
    main()
