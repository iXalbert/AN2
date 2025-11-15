package loose.oose.sef;

import java.util.*;

abstract class Document {
    protected List<String> content;

    public Document(List<String> content) {
        this.content = content;
    }

    public List<String> getContent() {
        return content;
    }

    public void setContent(List<String> content) {
        this.content = content;
    }

    public abstract List<String> analyze();

    public abstract String toString();
}

class XMLDocument extends Document {
    public XMLDocument(List<String> content) {
        super(content);
    }

    public List<String> analyze() {
        List<String> result = new ArrayList<>();
        for (String str : content) {
            if (!str.startsWith("<") || !str.endsWith(">")) {
                result.add(str);
            }
        }
        return result;
    }

    public String toString() {
        return "XML " + String.join(" ", content);
    }
}

class JSONDocument extends Document {
    public JSONDocument(List<String> content) {
        super(content);
    }

    public List<String> analyze() {
        List<String> result = new ArrayList<>();
        for (int i = 0; i < content.size(); i++) {
            if (i % 2 == 1) {
                result.add(content.get(i));
            }
        }
        return result;
    }

    public String toString() {
        return "JSON " + String.join(" ", content);
    }
}

abstract class Processor {
    public abstract int process(List<Document> documents);
}

class SearchProcessor extends Processor {
    private String query;

    public SearchProcessor(String query) {
        this.query = query;
    }

    public String getQuery() {
        return query;
    }

    public void setQuery(String query) {
        this.query = query;
    }

    @Override
    public int process(List<Document> documents) {
        int count = 0;
        for (Document doc : documents) {
            for (String str : doc.analyze()) {
                count += countOccurrences(str, query);
            }
        }
        return count;
    }

    private int countOccurrences(String text, String search) {
        int count = 0;
        int index = 0;
        while ((index = text.indexOf(search, index)) != -1) {
            count++;
            index += search.length();
        }
        return count;
    }
}

class CompositeProcessor extends Processor {
    private List<Processor> processors;

    public CompositeProcessor() {
        this.processors = new ArrayList<>();
    }

    public void addProcessor(Processor processor) {
        processors.add(processor);
    }

    @Override
    public int process(List<Document> documents) {
        int total = 0;
        for (Processor processor : processors) {
            total += processor.process(documents);
        }
        return total;
    }
}


public class Main {
    public static void main(String[] args) {
	
        Document xmlDoc = new XMLDocument(Arrays.asList("<tag>", "value1", "</tag>", "<tag>", "value2", "</tag>"));
        Document jsonDoc = new JSONDocument(Arrays.asList("name1", "value1", "name2", "value2"));

        List<Document> documents = Arrays.asList(xmlDoc, jsonDoc);

        SearchProcessor search1 = new SearchProcessor("value1");
        SearchProcessor search2 = new SearchProcessor("value2");
        SearchProcessor search3 = new SearchProcessor("nonexistent");

        CompositeProcessor composite1 = new CompositeProcessor();
        composite1.addProcessor(search1);
        composite1.addProcessor(search2);

        CompositeProcessor composite2 = new CompositeProcessor();
        composite2.addProcessor(composite1);
        composite2.addProcessor(search3);

        System.out.println("Număr total de apariții: " + composite2.process(documents));

        System.out.println("XML Document analizat: " + xmlDoc.analyze());
        System.out.println("JSON Document analizat: " + jsonDoc.analyze());
    }
}
