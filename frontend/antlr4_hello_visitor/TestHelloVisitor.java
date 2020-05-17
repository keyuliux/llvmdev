import org.antlr.v4.runtime.tree.ParseTreeVisitor;

public class TestHelloVisitor extends HelloBaseVisitor<Integer> {
    public Integer visitR(HelloParser.RContext ctx) {
        System.out.println("the ID is:"+ ctx.ID());
        return (1);
	}
}