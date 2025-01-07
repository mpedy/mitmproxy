import { Flow } from "../../flow";
import * as React from "react";
import ValueEditor from "../editors/ValueEditor";
import { useAppDispatch } from "../../ducks";
import * as flowActions from "../../ducks/flows";
//import { getMetadata } from "../../flow/utils";

export default function ProcessTree({ flow }: { flow: Flow }) {
    const dispatch = useAppDispatch();
    const processtree =flow.metadata ? flow.metadata["processtree"] : {}
    const columns = ["Depth","Process Name", "Type of process", "PID","Parent Process PID"];

    return (
        <section className="processtree">
            <h4>Process Tree</h4>
            <table style={{width: "100%"}}>
                <thead>
                    <tr>
                        <th>Depth</th>
                        <th>Process Name</th>
                        <th>Type of process</th>
                        <th>PID</th>
                        <th>Parent Process PID</th>
                    </tr>
                </thead>
                <tbody>
                    {processtree.map(function(x,y){
                        return (
                            <tr key={y}>
                                <td>{y}</td>
                                <td>{x["Caption"]}</td>
                                <td>{x["type_of_process"]}</td>
                                <td>{x["ProcessId"]}</td>
                                <td>{x["ParentProcessId"]}</td>
                            </tr>
                        )
                    })}
                </tbody>
            </table>

        </section>
    );
}
ProcessTree.displayName = "Process Tree";
